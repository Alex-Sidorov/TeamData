#include "workerdataclient.h"

#include <QDataStream>

void WorkerDataClient::change_data(QTcpSocket *client, TransferData &data)
{
    auto meta_data = parse_recved_data(data);
    _username[client] = meta_data.first;
    _clients_data[client] = std::make_tuple(meta_data.second,data);

    _worker_data_base.insert_user(_username[client]);
    _worker_data_base.delete_data_dir_user(meta_data.first);
    _worker_data_base.insert_data_dir_user(meta_data.first, meta_data.second.first);
    _worker_data_base.delete_data_files_user(meta_data.first);
    _worker_data_base.insert_data_files_user(meta_data.first, meta_data.second.second);
}

QPair<QString,WorkerDataClient::MetaDataDir> WorkerDataClient::parse_recved_data(TransferData &data)
{
    QDataStream stream(&data,QIODevice::ReadOnly);

    MetaDataDir meta_data;
    QString name;

    stream >> name >> meta_data.first;
    while(!stream.atEnd())
    {
        QString name_file;
        FileCharacteristics file_info;
        stream >> name_file >> std::get<0>(file_info)
                            >> std::get<1>(file_info)
                            >> std::get<2>(file_info);
        meta_data.second.insert(name_file,file_info);
    }
    return qMakePair(name, meta_data);
}

void WorkerDataClient::create_sended_data(QByteArray &data, const QList<QTcpSocket *> &users)
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
