#include "Workers/workerremoteclient.h"
#include "Tasks/tasksendfile.h"

#include <QFileInfo>
#include <QDateTime>

using namespace WorkRemoteDevice;

bool WorkerRemoteClient::run_serv()
{
    auto addr = _settings.read_self_addr();
    auto port = _settings.read_self_port();

    _serv.reset(new SERVER(addr, port));

    connect(_serv.get(),&SERVER::new_connection,this,[&]
    {
        _serv->add_connection();
    });

    connect(_serv.get(),&SERVER::disconnected_socket,this,[&](QTcpSocket *socket)
    {
        _serv->remove_connection(socket);
    });

    connect(_serv.get(),&SERVER::ready_data_read,this,&WorkerRemoteClient::slot_ready_read);

    return _serv->run();
}

void WorkerRemoteClient::slot_ready_read(QTcpSocket *socket)
{
    QByteArray data;
    _serv->read_data(socket, data);

    auto path = _settings.read_path() + '/' + data;
    path.replace('\\','/');

    QFileInfo info(path);
    if(info.isFile())
    {
        auto file = new QFile(path);
        if(file->open(QIODevice::ReadOnly))
        {
            auto task = new TasksClient::TaskSendFile(file,_proxy);
            connect(task,&TasksClient::TaskSendFile::send_data,this,[&,socket](QByteArray array)
            {
                if(!_serv.isNull())
                {
                    _serv->write_data(socket,array);
                }
            }, Qt::ConnectionType::QueuedConnection);
            _proxy->push(task);
        }
    }
    else
    {
        QByteArray msg = "null";
        _serv->write_data(socket, msg);
    }
}

void WorkerRemoteClient::download_file(const QString &src_file, const QString &dst_file, const QString &user)
{
    if(src_file.isEmpty() || dst_file.isEmpty())
    {
        emit error_name_file();
        return;
    }

    auto addr_info = _settings.get_addr_info_user(user);
    auto &addr = addr_info.first;
    auto &port = addr_info.second;

    auto client = new CLIENT(addr,port);

    _mutex_for_download.lock();
    auto work_info = &_info_for_recv[client];
    _mutex_for_download.unlock();

    connect(client,&CLIENT::ready_data_read,this,[client, work_info,this, dst_file,src_file,user]
    {
        QMutexLocker lock(&_mutex_for_download);

        QByteArray data;
        client->read_data(data);
        if(!work_info->_is_recved && data == "null")
        {
            _info_for_recv.remove(client);
            emit error_didnt_found_file();
            client->deleteLater();
            return;
        }
        else if(!work_info->_is_recved)
        {
            work_info->_file = new QFile(dst_file);
            if(!work_info->_file->open(QIODevice::WriteOnly))
            {
                delete work_info->_file;
                client->deleteLater();
                _info_for_recv.remove(client);
                emit error_open_file();
                return;
            }
        }

        auto task = new TasksClient::TaskRecvFile(work_info,data);
        connect(task,&TasksClient::TaskRecvFile::recved_data,client,[this, client,src_file,user]()
        {
            QMutexLocker lock(&_mutex_for_download);
            _info_for_recv.remove(client);
            client->deleteLater();

            auto date = std::get<2>(_settings.get_data_files_user(user)[src_file]);
            _settings.update_task_user(user,src_file,date);
            //emit downloaded_file();
        }, Qt::ConnectionType::QueuedConnection);
        _proxy->push(task);
    });

    connect(client,&CLIENT::socket_error,this,[client,this](QAbstractSocket::SocketError state)
    {
        qDebug() << state;
        emit error_connect_to_host();

        QMutexLocker lock(&_mutex_for_download);
        _info_for_recv.remove(client);
        client->deleteLater();
    });

    connect(client,&CLIENT::connected_socket,this,[src_file,client, this]
    {
        client->write_data(src_file.toUtf8());
        //emit connect_to_host();
    });

    client->connect_to_host();
}

void WorkerRemoteClient::work_task(const QString &user)
{
    auto tasks = _settings.get_all_task_user(user);
    auto &tasks_files = tasks.first.first;
    auto &tasks_local_files = tasks.first.second;
    auto &dates = tasks.second;
    int index = 0;
    for(auto &task_file : tasks_files)
    {
        auto files = _settings.get_data_files_user(user);
        if(files.find(task_file) != files.end())
        {
            if(!QFileInfo(tasks_local_files[index]).isFile()
                    || dates[index] != std::get<2>(files[task_file]))
            {
                download_file(task_file,tasks_local_files[index],user);
            }
        }
        else
        {
            _settings.delete_task_user(user,{task_file});
        }
        index++;
    }
}

void WorkerRemoteClient::stop_serv()
{
    _serv.reset();
}

bool WorkerRemoteClient::is_serv_run()const
{
    return _serv.isNull() ? false : _serv->is_run();
}

WorkerRemoteClient::WorkerRemoteClient(PROXY *proxy):
    _proxy(proxy)
{
}

WorkerRemoteClient::~WorkerRemoteClient()
{
    auto clients = _info_for_recv.keys();
    for(auto client : clients)
    {
        delete client;
    }
    _serv.reset();
}
