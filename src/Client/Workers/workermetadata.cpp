#include "Workers/workermetadata.h"
#include "FileSystemWatcher/filesystem_informer.h"
#include "Tasks/taskfilechanged.h"
#include "Tasks/taskdirchanged.h"
#include "Tasks/tasksendmsg.h"

#include <QDebug>
#include <QDataStream>
#include <QFileInfo>

using fsi = FileSystemWatcher::FileSystemInformer;
using namespace TasksClient;
using namespace WorkMetaDataOnClient;

void WorkerMetaData::scan_dir()
{
    _path = _settings.read_path();
    if(!_path.isEmpty())
    {
        remove_watcher_path();

        _name = _settings.read_name();

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

        emit upload_tree(_present_meta_data, _name);
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
        remove_watcher_path();
        _path = path;
        scan_dir();
    }
}

void WorkerMetaData::change_dir(QString &&path)
{
    if(!path.isEmpty())
    {
        remove_watcher_path();
        _path = path;
        scan_dir();
    }
}

void WorkerMetaData::remove_watcher_path()
{
    _watcher.removePath(_path);
    auto files = _watcher.files();
    for(auto &file : files)
    {
        _watcher.removePath(file);
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

    _name = _settings.read_name();
    stream << _settings.read_self_addr()
           << _settings.read_self_port()
           << _name
           << _present_meta_data.first
           << static_cast<size_t>(_present_meta_data.second.size());

    auto &map = _present_meta_data.second;
    for(auto it = map.begin(); it != map.end(); it++)
    {
        stream << it.key() << std::get<INDEX_SIZE>(it.value())
                           << std::get<INDEX_CREATED>(it.value())
                           << std::get<INDEX_LAST_MODIFIED>(it.value());
    }
}

void WorkerMetaData::parse_recved_data(QByteArray &data)
{
    _name = _settings.read_name();

    QDataStream stream(&data,QIODevice::ReadOnly);

    size_t count_user_data = 0;

    stream >> count_user_data;
    for(size_t i = 0; i < count_user_data; i++)
    {
        QByteArray useful_data;
        stream >> useful_data;

        QDataStream sub_stream(&useful_data,QIODevice::ReadOnly);

        size_t count_files;
        QString name;
        QString addr;
        quint16 port;
        MetaDataDir meta_data;

        sub_stream >> addr >> port >> name;
        if(name != _name)
        {
            sub_stream >> meta_data.first >> count_files;
            for(size_t j = 0; j < count_files; j++)
            {
                QString name_file;
                FileCharacteristics file_info;
                sub_stream >> name_file
                           >> std::get<INDEX_SIZE>(file_info)
                           >> std::get<INDEX_CREATED>(file_info)
                           >> std::get<INDEX_LAST_MODIFIED>(file_info);

                meta_data.second.insert(name_file,file_info);
            }
            _remote_meta_data[name] = meta_data;
            _users[name] = qMakePair(addr,port);

            _settings.add_user(name);
            _settings.change_data_dir_user(name,meta_data.first);
            _settings.change_data_files_user(name,meta_data.second);
            _settings.insert_addr_info_user(name,addr,port);
            emit upload_tree(meta_data, name);
        }        
    }
}

void WorkerMetaData::files_changed(const QString &path)
{
    _name = _settings.read_name();
    if(_proxy)
    {
        auto task = new TaskFileChanged(&_meta_data, &_present_meta_data, path, _path, &_mutex);
        connect(task,&TaskFileChanged::complete_task,this,[this]
        {
            emit upload_tree(_present_meta_data, _name);
        });
        _proxy->push(task);
    }
    else
    {
        TaskFileChanged task(&_meta_data, &_present_meta_data, path, _path);
        task.exec();
        emit upload_tree(_present_meta_data, _name);
    }

}

void WorkerMetaData::dir_changed(const QString &path)
{
    _name = _settings.read_name();
    if(_proxy)
    {
        auto task = new TaskDirChanged(&_meta_data, &_present_meta_data, path, _path, &_watcher, &_mutex);
        connect(task,&TaskDirChanged::complete_task,this,[this](bool is_changed)
        {
            if(is_changed)
            {
                emit upload_tree(_present_meta_data, _name);
            }
        });
        _proxy->push(task);
    }
    else
    {
        TaskDirChanged task(&_meta_data, &_present_meta_data, path, _path, &_watcher );
        if(task.exec())
        {
            emit upload_tree(_present_meta_data, _name);
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

           auto task = new TaskRecvMsg(&_info_recv_data,data);
           connect(task,&TaskRecvMsg::recved_data,_client,[this]()
           {
               parse_recved_data(_info_recv_data._msg);
               _info_recv_data.clear();
           }, Qt::ConnectionType::DirectConnection);
           _proxy->push(task);
       });
   }
}

WorkerMetaData::WorkerMetaData(PROXY *proxy, CLIENT *client):
    _proxy(proxy)
{
    _path = _settings.read_path();
    _name = _settings.read_name();

    connect(&_watcher,&QFileSystemWatcher::fileChanged,this,&WorkerMetaData::files_changed);
    connect(&_watcher,&QFileSystemWatcher::directoryChanged,this,&WorkerMetaData::dir_changed);

    connect(this,&WorkerMetaData::upload_tree,this,[this](MetaDataDir data, QString name)
    {
        if(_client && name == _name)
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

void WorkerMetaData::load_data_from_database()
{
    auto users = _settings.get_users();
    for(auto &user : users)
    {
        auto dirs = _settings.get_data_dir_user(user);
        auto files = _settings.get_data_files_user(user);
        MetaDataDir data = qMakePair(dirs,files);
        upload_tree(data,user);
    }
}

WorkerMetaData::~WorkerMetaData()
{}

