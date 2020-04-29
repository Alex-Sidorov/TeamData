#ifndef WORKERREMOTECLIENT_H
#define WORKERREMOTECLIENT_H

#include <QObject>
#include <QSharedPointer>
#include <QVector>
#include <QMap>

#include <BaseServer/base_server.h>
#include <BaseClient/base_client.h>
#include <workerclientdatabase.h>
#include <settings.h>
#include <ActiveObject/proxyactiveobject.h>
#include "taskrecvfile.h"

class WorkerRemoteClient : public QObject
{
    Q_OBJECT

    using CLIENT = DataTransfer::BaseClient;
    using SERVER = DataTransfer::BaseServer;
    using PROXY = ActiveObject::ProxyActiveObject;

public:
    WorkerRemoteClient(PROXY *proxy);
    virtual ~WorkerRemoteClient();

    void run_serv();
    void stop_serv();

    bool is_serv_run()const;

    QString parse_request(QByteArray &msg);

    void download_file(const QString &src_file, const QString &dst_file, const QString &addr, quint16 port);

public slots:
    void slot_ready_read(QTcpSocket *socket);

private:
    QSharedPointer<SERVER> _serv;
    PROXY *_proxy;

    Settings _settings;

    QMap<CLIENT*,TaskRecvFile::WorkInfo> _info_for_recv;
};

#endif // WORKERREMOTECLIENT_H