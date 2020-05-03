#include "workerdataclient.h"

#include <QDataStream>
#include <QHostAddress>

void WorkerDataClient::change_data(QTcpSocket *client, TransferData &data)
{
    auto parse_data = parse_recved_data(data);
    auto user_info = std::get<0>(parse_data);
    auto meta_data = std::get<1>(parse_data);

    _username[client] = meta_data.first;
    _clients_data[client] = std::make_tuple(meta_data.second,data);

    WorkerServerDataBase worker_data_base;
    worker_data_base.insert_user(_username[client]);
    worker_data_base.delete_data_dir_user(meta_data.first);
    worker_data_base.insert_data_dir_user(meta_data.first, meta_data.second.first);
    worker_data_base.delete_data_files_user(meta_data.first);
    worker_data_base.insert_data_files_user(meta_data.first, meta_data.second.second);
    if(!worker_data_base.is_user_info(meta_data.first))
    {
        worker_data_base.insert_addr_info_user(meta_data.first,user_info.first,user_info.second);
    }
    else
    {
        worker_data_base.change_addr_user(meta_data.first,user_info.first);
        worker_data_base.change_port_user(meta_data.first,user_info.second);
    }
}

std::tuple<WorkerDataClient::UserAddrInfo,QPair<QString,WorkerDataClient::MetaDataDir>>
WorkerDataClient::parse_recved_data(TransferData &data)
{
    QDataStream stream(&data,QIODevice::ReadOnly);

    MetaDataDir meta_data;
    QString name;

    QString addr;
    quint16 port;

    size_t count_files = 0;
    stream >> addr >> port >> name >> meta_data.first >> count_files;
    for(size_t i = 0; i < count_files; i++)
    {
        QString name_file;
        FileCharacteristics file_info;
        stream >> name_file >> std::get<0>(file_info)
                            >> std::get<1>(file_info)
                            >> std::get<2>(file_info);
        meta_data.second.insert(name_file,file_info);
    }
    return std::make_tuple(qMakePair(addr,port),qMakePair(name, meta_data));
}

void WorkerDataClient::fill_transfers_data(QByteArray &data, const QList<QTcpSocket *> &users)
{
    QDataStream stream(&data,QIODevice::WriteOnly);

    auto temp = users;
    for(auto it = users.begin(); it != users.end(); it++)
    {
        if(_clients_data.find(*it) == _clients_data.end())
        {
            temp.removeOne(*it);
        }
    }

    stream << static_cast<size_t>(temp.size());
    for(auto user : temp)
    {
        stream << std::get<1>(_clients_data[user]);
    }
}


WorkerDataClient::MetaDataDir WorkerDataClient::get_metadata(QTcpSocket *client)
{
    if(_clients_data.find(client) != _clients_data.end())
    {
        return std::get<0>(_clients_data[client]);
    }
    else
    {
        return {};
    }
}

WorkerDataClient::TransferData WorkerDataClient::get_transfer_data(QTcpSocket *client)
{
    if(_clients_data.find(client) != _clients_data.end())
    {
        return std::get<1>(_clients_data[client]);
    }
    else
    {
        return {};
    }
}

void WorkerDataClient::get_full_meta_data(QByteArray &data, const QStringList& filter)
{
    WorkerServerDataBase worker_data_base;
    auto users = worker_data_base.get_all_user();

    for(auto &user : filter)
    {
        users.removeOne(user);
    }

    QDataStream stream(&data,QIODevice::WriteOnly);
    stream << static_cast<size_t>(users.size());

    auto it = _clients_data.begin();
    while(it != _clients_data.end())
    {
        users.removeOne(_username[it.key()]);
        stream << std::get<1>(it.value());
        ++it;
    }

    for(auto &user : users)
    {
        QByteArray temp;
        auto pair = qMakePair(worker_data_base.get_data_dir_user(user),worker_data_base.get_data_files_user(user));
        create_sended_data(temp, user, pair);
        stream << temp;
    }
}

void WorkerDataClient::create_sended_data(QByteArray &data, QString &name, MetaDataDir &meta_data)
{
    QDataStream stream(&data,QIODevice::WriteOnly);

    WorkerServerDataBase worker;
    auto addr_info = worker.get_addr_info_user(name);
    stream << addr_info.first
           << addr_info.second
           << name
           << meta_data.first
           << static_cast<size_t>(meta_data.second.size());

    auto &map = meta_data.second;
    for(auto it = map.begin(); it != map.end(); it++)
    {
        stream << it.key() << std::get<0>(it.value())
                           << std::get<2>(it.value())
                           << std::get<1>(it.value());
    }
}

bool WorkerDataClient::remove_client(QTcpSocket *client)
{
    _username.remove(client);
    return _clients_data.remove(client);
}

WorkerDataClient::WorkerDataClient()
{
}

WorkerDataClient::~WorkerDataClient()
{
}
