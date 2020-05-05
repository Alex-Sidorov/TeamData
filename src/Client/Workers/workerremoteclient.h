#ifndef WORKERREMOTECLIENT_H
#define WORKERREMOTECLIENT_H

#include "BaseServer/base_server.h"
#include "BaseClient/base_client.h"
#include "Workers/workerclientdatabase.h"
#include "Settings/settings.h"
#include "ActiveObject/proxyactiveobject.h"
#include "Tasks/taskrecvfile.h"

#include <QObject>
#include <QSharedPointer>
#include <QVector>
#include <QMap>
#include <QMutex>

namespace WorkRemoteDevice
{
    class WorkerRemoteClient : public QObject
    {
        Q_OBJECT

        using CLIENT = DataTransfer::BaseClient;
        using SERVER = DataTransfer::BaseServer;
        using PROXY = ActiveObject::ProxyActiveObject;

    signals:
        void error_name_file();
        void error_open_file();
        void error_connect_to_host();
        void error_didnt_found_file();
        void connect_to_host();
        void downloaded_file();

    public:
        WorkerRemoteClient(PROXY *proxy);
        virtual ~WorkerRemoteClient();

        bool run_serv();
        void stop_serv();

        bool is_serv_run()const;

        QString parse_request(QByteArray &msg);

        void download_file(const QString &src_file, const QString &dst_file, const QString &user);

        void work_task(const QString &user);

    public slots:
        void slot_ready_read(QTcpSocket *socket);

    private:
        QSharedPointer<SERVER> _serv;
        PROXY *_proxy;

        SettingsClient::Settings _settings;

        QMap<CLIENT*,TasksClient::TaskRecvFile::WorkInfo> _info_for_recv;
        QMutex _mutex_for_download;

        static constexpr const char* FORMAT_DATE = "dd.MM.yyyy hh:mm:ss";
    };
}

#endif // WORKERREMOTECLIENT_H
