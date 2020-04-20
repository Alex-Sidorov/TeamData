#include "workerdataclient.h"

#include <QDataStream>

void WorkerDataClient::change_data(QTcpSocket *client, TransferData &data)
{
    auto meta_data = parse_recved_data(data);
    _clients_data[client] = std::make_tuple(meta_data,data);
}

WorkerDataClient::MetaDataDir WorkerDataClient::parse_recved_data(TransferData &data)
{
    QDataStream stream(&data,QIODevice::ReadOnly);

    MetaDataDir meta_data;

    stream >> meta_data.first ;
    while(!stream.atEnd())
    {
        QString name_file;
        FileCharacteristics file_info;
        stream >> name_file >> std::get<0>(file_info)
                            >> std::get<1>(file_info)
                            >> std::get<2>(file_info);
        meta_data.second.insert(name_file,file_info);
    }
    return meta_data;
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

WorkerDataClient::WorkerDataClient()
{
}

WorkerDataClient::~WorkerDataClient()
{
}
