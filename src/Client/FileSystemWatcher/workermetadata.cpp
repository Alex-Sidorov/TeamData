#include "workermetadata.h"
#include "filesystem_informer.h"

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

        _watcher.addPaths({_path, "D:/dir/папка/1"});//todo
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

void WorkerMetaData::remove_root_path(QString &path, QStringList &data) const
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

//todo
void WorkerMetaData::files_changed(const QString &path)
{
    QFileInfo info(path);
    if(info.isFile())
    {
        QStringList list{path};
        auto size_files = fsi::get_size_files(list);
        auto date_last_modified_files = fsi::get_date_last_modified_files(list);
        auto date_create_files = fsi::get_date_created_files(list);
        _meta_data.second[path] = std::make_tuple(size_files[0],date_create_files[0],date_last_modified_files[0]);
        auto temp = path.mid(_path.size());
        _present_meta_data.second[temp] = std::make_tuple(size_files[0],date_create_files[0],date_last_modified_files[0]);
    }
    else
    {
        _meta_data.second.remove(path);
        auto temp = path.mid(_path.size());
        _present_meta_data.second.remove(temp);
        //_tree.remove_file(path);
    }
    emit upload_tree(_present_meta_data);
    qDebug() << "f" << path;
}

//todo
void WorkerMetaData::dir_changed(const QString &path)
{
    auto dirs = fsi::get_terminal_directories(path);
    auto new_dirs = get_added_folders(dirs);
    auto removed_dirs = get_removed_folders(dirs,path);

    if(new_dirs.size())
    {
        for(int i = 0; i < new_dirs.size(); i++)
        {
            _meta_data.first.push_back(new_dirs[i]);
            _present_meta_data.first.push_back(new_dirs[i].mid(_path.size()));
        }
    }
    if(removed_dirs.size())
    {
        for(int i = 0; i < removed_dirs.size(); i++)
        {
            _meta_data.first.removeOne(removed_dirs[i]);
            _present_meta_data.first.removeOne(removed_dirs[i].mid(_path.size()));
        }
    }

    auto files = fsi::get_files(path);
    auto new_files = get_added_files(files);
    auto removed_files = get_removed_files(files,path);

    if(new_files.size())
    {
        _watcher.addPaths(new_files);
        auto size_files = fsi::get_size_files(new_files);
        auto date_last_modified_files = fsi::get_date_last_modified_files(new_files);
        auto date_create_files = fsi::get_date_created_files(new_files);
        for(int i = 0; i < new_files.size(); i++)
        {
            _meta_data.second.insert(new_files[i],std::make_tuple(size_files[i],date_create_files[i],date_last_modified_files[i]));
            _present_meta_data.second.insert(new_files[i].mid(_path.size()),std::make_tuple(size_files[i],date_create_files[i],date_last_modified_files[i]));
        }
    }

    if(removed_files.size())
    {
        _watcher.removePaths(removed_files);
        for(auto &file : removed_files)
        {
            _meta_data.second.remove(file);
            _present_meta_data.second.remove(file.mid(_path.size()));
        }
    }

    emit upload_tree(_present_meta_data);
    qDebug() << "d" << path;

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

WorkerMetaData::WorkerMetaData(QString &path):_path(path)
{
    scan_dir();
    connect(&_watcher,&QFileSystemWatcher::fileChanged,this,&WorkerMetaData::files_changed);
    connect(&_watcher,&QFileSystemWatcher::directoryChanged,this,&WorkerMetaData::dir_changed);
}

WorkerMetaData::WorkerMetaData(QString &&path):_path(path)
{
    scan_dir();
    connect(&_watcher,&QFileSystemWatcher::fileChanged,this,&WorkerMetaData::files_changed);
    connect(&_watcher,&QFileSystemWatcher::directoryChanged,this,&WorkerMetaData::dir_changed);
}

WorkerMetaData::WorkerMetaData()
{
    connect(&_watcher,&QFileSystemWatcher::fileChanged,this,&WorkerMetaData::files_changed);
    connect(&_watcher,&QFileSystemWatcher::directoryChanged,this,&WorkerMetaData::dir_changed);
}

WorkerMetaData::~WorkerMetaData()
{}
