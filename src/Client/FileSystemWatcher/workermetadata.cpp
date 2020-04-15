#include "workermetadata.h"
#include "filesystem_informer.h"
#include "taskfilechanged.h"
#include "taskdirchanged.h"

#include <QDebug>
#include <QDataStream>
#include <QFileInfo>

using fsi = FileSystemWatcher::FileSystemInformer;

void WorkerMetaData::scan_dir()
{
    if(!_path.isEmpty())
    {
        auto dirs = fsi::get_terminal_directories(_path);
        auto present_dirs = dirs;
        remove_root_path(_path,present_dirs);
        //dirs.push_front(_path);

        auto files = fsi::get_files(_path);
        auto present_files = files;
        remove_root_path(_path,present_files);

        //init_dir_tree(files,present_dirs);

        _watcher.addPath(_path);
        add_dirs_path(present_dirs);
        _watcher.addPaths(files);

        auto size_files = fsi::get_size_files(files);
        auto date_last_modified_files = fsi::get_date_last_modified_files(files);
        auto date_create_files = fsi::get_date_created_files(files);

        FileMetaData data;
        FileMetaData present_data;
        for(int i = 0; i < files.size(); i++)
        {
            data.insert(files[i],std::make_tuple(size_files[i],date_create_files[i],date_last_modified_files[i]));
            present_data.insert(present_files[i],std::make_tuple(size_files[i],date_create_files[i],date_last_modified_files[i]));
        }

        _meta_data = qMakePair(dirs,data);
        _present_meta_data = qMakePair(present_dirs, present_data);

        emit upload_tree(_present_meta_data);
    }
}

void WorkerMetaData::add_dirs_path(QStringList &dirs)
{
    for(auto &dir:dirs)
    {
        auto path = dir.split('/');
        path.removeAll("");
        auto temp = _path + '/';
        for (int i = 0; i < path.size(); i++)
        {
            temp += path[i] + '/';
            if(!(i % 2 == 0))
            {
                _watcher.addPath(temp);
            }
        }
    }
}

void WorkerMetaData::change_dir(QString &path)
{
    if(!path.isEmpty())
    {
        _path = path;
    }
}

void WorkerMetaData::change_dir(QString &&path)
{
    if(!path.isEmpty())
    {
        _path = path;
    }
}

void WorkerMetaData::remove_root_path(QString &path, QStringList &data)
{
    path.replace("\\","/");
    for(auto &value : data)
    {
        value.remove(path);
    }
}

void WorkerMetaData::create_sended_data(QByteArray &data)
{
    QDataStream stream(&data,QIODevice::WriteOnly);
    stream << _present_meta_data.first;

    auto &map = _present_meta_data.second;
    for(auto it = map.begin(); it != map.end(); it++)
    {
        stream << it.key() << std::get<0>(it.value())
                           << std::get<1>(it.value())
                           << std::get<2>(it.value());
    }
}

void WorkerMetaData::files_changed(const QString &path)
{
    if(_proxy)
    {
        auto task = new TaskFileChanged(&_meta_data, &_present_meta_data, path, _path, &_mutex);
        connect(task,&TaskFileChanged::complete_task,this,[this]
        {
            emit upload_tree(_present_meta_data);
        });
        _proxy->push(task);
    }
    else
    {
        TaskFileChanged task(&_meta_data, &_present_meta_data, path, _path);
        task.exec();
        emit upload_tree(_present_meta_data);
    }

}

void WorkerMetaData::dir_changed(const QString &path)
{
    if(_proxy)
    {
        auto task = new TaskDirChanged(&_meta_data, &_present_meta_data, path, _path, &_watcher, &_mutex);
        connect(task,&TaskDirChanged::complete_task,this,[this](bool is_changed)
        {
            if(is_changed)
            {
                emit upload_tree(_present_meta_data);
            }
        });
        _proxy->push(task);
    }
    else
    {
        TaskDirChanged task(&_meta_data, &_present_meta_data, path, _path, &_watcher );
        if(task.exec())
        {
            emit upload_tree(_present_meta_data);
        }
    }
}

QStringList WorkerMetaData::get_removed_files(const QStringList &scan_files, const QString &path)const
{
    QStringList result;
    auto it = _meta_data.second.begin();
    while(it != _meta_data.second.end())
    {
        if(it.key().indexOf(path) != -1 && it.key()[path.size()] == '/' && scan_files.indexOf(it.key()) == -1)
        {
            result.append(it.key());
        }
        ++it;
    }
    return result;
}

QStringList WorkerMetaData::get_added_files(const QStringList &scan_files)const
{
    auto files = scan_files;
    auto it = _meta_data.second.begin();
    while(it != _meta_data.second.end())
    {
        files.removeOne(it.key());
        ++it;
    }
    return files;
}

QStringList WorkerMetaData::get_removed_folders(const QStringList &scan_dirs, const QString &path)const
{
    QStringList result;
    for(auto &dir : _meta_data.first)
    {
        if(dir.indexOf(path) != -1 && dir != path && scan_dirs.indexOf(dir) == -1)
        {
            result.append(dir);
        }
    }
    return result;
}

QStringList WorkerMetaData::get_added_folders(const QStringList &scan_dirs)const
{
    auto dirs = scan_dirs;
    for(auto &dir : _meta_data.first)
    {
        dirs.removeOne(dir);
    }
    return dirs;
}

WorkerMetaData::WorkerMetaData(PROXY *proxy, QString &path):
    _path(path),
    _proxy(proxy)
{
    scan_dir();
    connect(&_watcher,&QFileSystemWatcher::fileChanged,this,&WorkerMetaData::files_changed);
    connect(&_watcher,&QFileSystemWatcher::directoryChanged,this,&WorkerMetaData::dir_changed);
}

WorkerMetaData::WorkerMetaData(PROXY *proxy, QString &&path):
    _path(path),
    _proxy(proxy)
{
    scan_dir();
    connect(&_watcher,&QFileSystemWatcher::fileChanged,this,&WorkerMetaData::files_changed);
    connect(&_watcher,&QFileSystemWatcher::directoryChanged,this,&WorkerMetaData::dir_changed);
}

WorkerMetaData::WorkerMetaData(PROXY *proxy):_proxy(proxy)
{
    connect(&_watcher,&QFileSystemWatcher::fileChanged,this,&WorkerMetaData::files_changed);
    connect(&_watcher,&QFileSystemWatcher::directoryChanged,this,&WorkerMetaData::dir_changed);
}

WorkerMetaData::~WorkerMetaData()
{}

/*void WorkerMetaData::insert_dir(QString &dir)
{
    auto path = dir.split('/');
    auto *tree = &_tree;
    for (int i = 0; i < path.size(); i++)
    {
        if(path[i].isEmpty())continue;

        bool be_dir = false;
        for(auto &cur_branch_dir : tree->dirs)
        {
            if(cur_branch_dir.name.split('/').last() == path[i])
            {
                be_dir = true;
                tree = &cur_branch_dir;
                break;
            }
        }
        if(!be_dir)
        {
            tree->dirs.push_back(DirTree{});
            tree->dirs.last().name = tree->name + '/' + path[i];
            tree->dirs.last().last_modify = QFileInfo(tree->name).lastModified();
            tree = &tree->dirs.last();
        }
    }
}

void WorkerMetaData::insert_file(DirTree &tree, QString &file)
{
    if(file.indexOf(tree.name) != -1)
    {
        if(tree.name + '/' == file.mid(0,file.indexOf(file.split('/').last())))
        {
            tree.files.push_back(file);
            return;
        }
        for (auto &sub_dir : tree.dirs)
        {
            if(file.indexOf(sub_dir.name) != -1)
            {
                insert_file(sub_dir,file);
                break;
            }
        }
    }
}

void WorkerMetaData::init_dir_tree(QStringList &files, QStringList &dirs)
{
    _tree.name = _path;
    _tree.last_modify = QFileInfo(_tree.name).lastModified();
    for(auto &v : dirs)
    {
        insert_dir(v);
    }
    for(auto &v : files)
    {
       insert_file(_tree,v);
    }
}*/
