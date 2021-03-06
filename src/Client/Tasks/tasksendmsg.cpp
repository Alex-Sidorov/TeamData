#include "Tasks/tasksendmsg.h"

void TasksClient::TaskSendMsg::run_process()
{
    if(_msg.isEmpty())
    {
        delete this;
        return;
    }

    QByteArray data;

    if(!_is_sended)
    {
        data = BaseClient::IntToArray(_msg.size());
        _is_sended = true;
    }

    data += _msg.mid(0,static_cast<int>(_MTU));
    _msg.remove(0,static_cast<int>(_MTU));

    emit send_data(data);

    if(_msg.isEmpty())
    {
        delete this;
    }
    else
    {
        _proxy->push(this);
    }
}

TasksClient::TaskSendMsg::TaskSendMsg(QByteArray &msg, ProxyActiveObject *proxy, uint32_t MTU):
    _msg(msg), _proxy(proxy), _MTU(MTU), _is_sended(false)
{
}

TasksClient::TaskSendMsg::~TaskSendMsg()
{

}
