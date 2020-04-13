#ifndef TASKSENDMSG_H
#define TASKSENDMSG_H

#include <ActiveObject/abstracttask.h>
#include <ActiveObject/proxyactiveobject.h>
#include <BaseServer/base_server.h>

using DataTransfer::BaseServer;
using ActiveObject::ProxyActiveObject;

class TaskSendMsg : public ActiveObject::AbstractTask
{
/*public:
    void run_process() override;

    TaskSendMsg(BaseClient* client, QByteArray msg, ProxyActiveObject *proxy, uint32_t MTU = 1500);
    virtual ~TaskSendMsg() override;

private:
    BaseClient *_client;
    QByteArray _msg;
    ProxyActiveObject *_proxy;
    uint32_t _MTU;
    bool _is_sended;*/
};

#endif // TASKSENDMSG_H
