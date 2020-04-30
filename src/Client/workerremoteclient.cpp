#include "workerremoteclient.h"
#include "tasksendfile.h"

#include <QFileInfo>

bool WorkerRemoteClient::run_serv()
{
    _settings.read_settings();

    auto addr = _settings.get_self_addr();
    auto port = _settings.get_self_port();

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

    auto path = _settings.get_path() + '/' + data;
    path.replace('\\','/');

    QFileInfo info(path);
    if(info.isFile())
    {
        auto file = new QFile(path);
        if(file->open(QIODevice::ReadOnly))
        {
            auto task = new TaskSendFile(file,_proxy);
            connect(task,&TaskSendFile::send_data,this,[&,socket](QByteArray array)
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

void WorkerRemoteClient::download_file(const QString &src_file, const QString &dst_file, const QString &addr, quint16 port)
{
    if(src_file.isEmpty() || dst_file.isEmpty())
    {
        emit error_name_file();
        return;
    }

    auto client = new CLIENT(addr,port);
    auto work_info = &_info_for_recv[client];

    connect(client,&CLIENT::ready_data_read,this,[client, work_info,this, dst_file]
    {
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

        auto task = new TaskRecvFile(work_info,data);
        connect(task,&TaskRecvFile::recved_data,client,[this, client]()
        {
            _info_for_recv.remove(client);
            client->deleteLater();
            emit downloaded_file();
        }, Qt::ConnectionType::QueuedConnection);
        _proxy->push(task);
    });

    connect(client,&CLIENT::socket_error,this,[client,this](QAbstractSocket::SocketError state)
    {
        qDebug() << state;
        emit error_connect_to_host();
        _info_for_recv.remove(client);
        client->deleteLater();
    });

    connect(client,&CLIENT::connected_socket,this,[src_file,client, this]
    {
        client->write_data(src_file.toUtf8());
        emit connect_to_host();
    });

    client->connect_to_host();
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
