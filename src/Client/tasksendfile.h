#ifndef TASKSENDFILE_H
#define TASKSENDFILE_H

#include <QObject>
#include <QFile>

#include <ActiveObject/abstracttask.h>
#include <ActiveObject/proxyactiveobject.h>
#include <BaseClient/base_client.h>

using ActiveObject::ProxyActiveObject;

class TaskSendFile : public QObject, public ActiveObject::AbstractTask
{
    Q_OBJECT

    using Client = DataTransfer::BaseClient;
    using PROXY = ActiveObject::ProxyActiveObject;

public:
    TaskSendFile(QFile *file, PROXY *proxy, uint32_t MTU = 1500);
    virtual ~TaskSendFile() override;

    void run_process() override;

signals:
    void send_data(QByteArray array);

private:
    QFile *_file;
    PROXY *_proxy;
    uint32_t _MTU;
    bool _is_sended;
};

#endif // TASKSENDFILE_H
