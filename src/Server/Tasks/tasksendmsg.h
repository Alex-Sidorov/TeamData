#ifndef TASKSENDMSG_H
#define TASKSENDMSG_H

#include <QObject>

#include <ActiveObject/abstracttask.h>
#include <ActiveObject/proxyactiveobject.h>
#include <BaseServer/base_server.h>


using DataTransfer::BaseServer;
using ActiveObject::ProxyActiveObject;

class TaskSendMsg : public QObject, public ActiveObject::AbstractTask
{
    Q_OBJECT
signals:
    void send_data(QByteArray array);
public:

    void run_process() override;

    TaskSendMsg(QByteArray &msg, ProxyActiveObject *proxy, uint32_t MTU = 1500);
    virtual ~TaskSendMsg() override;

private:
    QByteArray _msg;
    ProxyActiveObject *_proxy;
    uint32_t _MTU;
    bool _is_sended;
};

#endif // TASKSENDMSG_H
