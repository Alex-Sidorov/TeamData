#ifndef WORKERDATACLIENT_H
#define WORKERDATACLIENT_H

#include "workerserverdatabase.h"

#include <QByteArray>
#include <QStringList>
#include <QMap>
#include <QTcpSocket>

#include <tuple>

class WorkerDataClient
{
    using TransferData = QByteArray;
    using FileCharacteristics = std::tuple<quint64,QString,QString>;
    using FileMetaData = QMap<QString,FileCharacteristics>;
    using DirsPath = QStringList;


public:
    using MetaDataDir = QPair<DirsPath,FileMetaData>;

    WorkerDataClient();
    virtual ~WorkerDataClient();

    void change_data(QTcpSocket *client, TransferData &data);

    TransferData get_transfer_data(QTcpSocket *client);
    MetaDataDir get_metadata(QTcpSocket *client);

    bool remove_client(QTcpSocket *client);

    void create_sended_data(QByteArray &data, const QList<QTcpSocket*> &source);

private:
    QMap<QTcpSocket*,std::tuple<MetaDataDir,TransferData>> _clients_data;
    QMap<QTcpSocket*,QString> _username;

    QPair<QString,MetaDataDir> parse_recved_data(QByteArray &data);
};

#endif // WORKERDATACLIENT_H
