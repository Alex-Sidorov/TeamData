#include "workermetadata.h"
#include "filesystem_informer.h"
#include "taskfilechanged.h"
#include "taskdirchanged.h"

#include <QDebug>
#include <QDataStream>
#include <QFileInfo>

#include "tasksendmsg.h"

using fsi = FileSystemWatcher::FileSystemInformer;

void WorkerMetaData::scan_dir()
{
    if(!_path.isEmpty())
    {
        auto dirs = fsi::get_terminal_directories(_path);
        auto present_dirs = dirs;
        remove_root_path(_path,present_dirs);

        auto files = fsi::get_files(_path);
        auto present_files = files;
        remove_root_path(_path,present_files);

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

    QMutexLocker lock(&_mutex);
    stream << _present_meta_data.first;

    auto &map = _present_meta_data.second;
    for(auto it = map.begin(); it != map.end(); it++)
    {
        stream << it.key() << std::get<0>(it.value())
                           << std::get<1>(it.value())
                           << std::get<2>(it.value());
    }
}

void WorkerMetaData::parse_recved_data(QByteArray &data)
{
    QDataStream stream(&data,QIODevice::ReadOnly);

    size_t count_user_data;

    stream >> count_user_data;
    for(size_t i = 0; i < count_user_data; i++)
    {
        int count_files;
        QString name;
        QString addr;
        MetaDataDir meta_data;

        stream >> addr >> name >> meta_data.first >> count_files;
        for(int j = 0; j < count_files; j++)
        {
            QString name_file;
            FileCharacteristics file_info;
            stream >> name_file >> std::get<0>(file_info)
                                >> std::get<1>(file_info)
                                >> std::get<2>(file_info);
            meta_data.second.insert(name_file,file_info);
        }
        _remote_meta_data[qMakePair(name,addr)] = meta_data;
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

void WorkerMetaData::change_client(CLIENT *client)
{
   _client = client;
   if(_client)
   {
       connect(_client,&CLIENT::ready_data_read,this,[this]
       {
           QByteArray data;
           _client->read_data(data);

           auto task = new TaskRecvMsg(&info_recv_data,data);
           connect(task,&TaskRecvMsg::recved_data,_client,[this]()
           {
               parse_recved_data(info_recv_data._msg);
               info_recv_data.clear();
           }, Qt::ConnectionType::DirectConnection);
           _proxy->push(task);
       });
   }
}

WorkerMetaData::WorkerMetaData(PROXY *proxy, QString &path, CLIENT *client):
    _path(path),
    _proxy(proxy)
{
    scan_dir();
    connect(&_watcher,&QFileSystemWatcher::fileChanged,this,&WorkerMetaData::files_changed);
    connect(&_watcher,&QFileSystemWatcher::directoryChanged,this,&WorkerMetaData::dir_changed);

    connect(this,&WorkerMetaData::upload_tree,this,[this]
    {
        if(_client)
        {
            QByteArray temp;
            create_sended_data(temp);
            auto task = new TaskSendMsg(temp,_proxy);
            connect(task,&TaskSendMsg::send_data,_client,[&](QByteArray array)
            {
                _client->write_data(array);
            }, Qt::ConnectionType::QueuedConnection);
            _proxy->push(task);
        }
    });

    change_client(client);
}

WorkerMetaData::WorkerMetaData(PROXY *proxy, QString &&path, CLIENT *client):
    _path(path),
    _proxy(proxy)
{
    scan_dir();
    connect(&_watcher,&QFileSystemWatcher::fileChanged,this,&WorkerMetaData::files_changed);
    connect(&_watcher,&QFileSystemWatcher::directoryChanged,this,&WorkerMetaData::dir_changed);

    connect(this,&WorkerMetaData::upload_tree,this,[this]
    {
        if(_client)
        {
            QByteArray temp;
            create_sended_data(temp);
            auto task = new TaskSendMsg(temp,_proxy);
            connect(task,&TaskSendMsg::send_data,_client,[&](QByteArray array)
            {
                _client->write_data(array);
            }, Qt::ConnectionType::QueuedConnection);
            _proxy->push(task);
        }
    });

    change_client(client);
}

WorkerMetaData::WorkerMetaData(PROXY *proxy, CLIENT *client):
    _proxy(proxy)
{
    connect(&_watcher,&QFileSystemWatcher::fileChanged,this,&WorkerMetaData::files_changed);
    connect(&_watcher,&QFileSystemWatcher::directoryChanged,this,&WorkerMetaData::dir_changed);

    connect(this,&WorkerMetaData::upload_tree,this,[this]
    {
        if(_client)
        {
            QByteArray temp;
            create_sended_data(temp);
            auto task = new TaskSendMsg(temp,_proxy);
            connect(task,&TaskSendMsg::send_data,_client,[&](QByteArray array)
            {
                _client->write_data(array);
            }, Qt::ConnectionType::QueuedConnection);
            _proxy->push(task);
        }
    });

    change_client(client);
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
