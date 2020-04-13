#include "taskrecvmsg.h"

void TaskRecvMsg::run_process()
{
    QByteArray temp;
    _serv->read_data(_client,temp);

    if(!_is_recved)
    {
        _is_recved = true;
        _size = BaseServer::ArrayToInt(temp);
        temp.remove(0,sizeof (_size));
    }
    if(temp.size())
    {
        _msg += temp;
        _size -= temp.size() + sizeof (_size);
    }

    if(_size > 0)
    {
        _proxy->push(this,100,ActiveObject::Scheduler::TypeDefferedTask::EXPRESS);
        return;
    }
    emit _serv->recved_data();
}

QByteArray TaskRecvMsg::get_msg()const
{
    return _msg;
}

TaskRecvMsg::~TaskRecvMsg()
{

}

TaskRecvMsg::TaskRecvMsg(BaseServer* serv,QTcpSocket *client, ProxyActiveObject *proxy):
    _serv(serv), _client(client), _proxy(proxy), _size(0), _is_recved(false)
{

}
