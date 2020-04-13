#ifndef TASKRECVMSG_H
#define TASKRECVMSG_H


#include <ActiveObject/abstracttask.h>
#include <ActiveObject/proxyactiveobject.h>
#include <BaseServer/base_server.h>

using DataTransfer::BaseServer;
using ActiveObject::ProxyActiveObject;

class TaskRecvMsg : public ActiveObject::AbstractTask
{
public:
    void run_process() override;

    QByteArray get_msg()const;

    TaskRecvMsg(BaseServer* serv, QTcpSocket *client, ProxyActiveObject *proxy);
    virtual ~TaskRecvMsg() override;

private:
    BaseServer *_serv;
    QTcpSocket *_client;
    QByteArray _msg;
    ProxyActiveObject *_proxy;
    qint32 _size;
    bool _is_recved;
};

#endif // TASKRECVMSG_H
