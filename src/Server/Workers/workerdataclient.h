#ifndef WORKERDATACLIENT_H
#define WORKERDATACLIENT_H

#include "Workers/workerserverdatabase.h"

#include <QByteArray>
#include <QStringList>
#include <QMap>
#include <QTcpSocket>

#include <tuple>

namespace WorkDataClientOnServer
{
    class WorkerDataClient
    {
        using TransferData = QByteArray;
        using FileCharacteristics = std::tuple<quint64,QString,QString>;
        using FileMetaData = QMap<QString,FileCharacteristics>;
        using DirsPath = QStringList;
        using UserAddrInfo = QPair<QString,quint16>;
        using MetaDataDir = QPair<DirsPath,FileMetaData>;

    public:
        WorkerDataClient();
        virtual ~WorkerDataClient();

        void change_data(QTcpSocket *client, TransferData &data);

        TransferData get_transfer_data(QTcpSocket *client);
        MetaDataDir get_metadata(QTcpSocket *client);

        bool remove_client(QTcpSocket *client);

        void fill_transfers_data(QByteArray &data, const QList<QTcpSocket*> &source);

        void get_full_meta_data(QByteArray &data, const QStringList& filter = {});

        void created_transfer_data(QByteArray &data, QString &name, MetaDataDir &meta_data, DataBaseWork::WorkerServerDataBase &worker);

    private:
        QMap<QTcpSocket*,std::tuple<MetaDataDir,TransferData>> _clients_data;
        QMap<QTcpSocket*,QString> _username;

        std::tuple<UserAddrInfo,QPair<QString,MetaDataDir>> parse_recved_data(QByteArray &data);

        static constexpr int INDEX_SIZE = 0;
        static constexpr int INDEX_LAST_MODIFIED = 1;
        static constexpr int INDEX_CREATED = 2;

        static constexpr int INDEX_PARSE_DATA = 0;
        static constexpr int INDEX_TRANSFER_DATA = 1;
    };
}

#endif // WORKERDATACLIENT_H
