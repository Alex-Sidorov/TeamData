#include "taskrecvmsg.h"

void TaskRecvMsg::run_process()
{
    if(_new_data.isEmpty())
    {
        return;
    }

    if(!_info->_size)
    {
        _info-> _size = DataTransfer::BaseServer::ArrayToInt(_new_data);
        _new_data.remove(0,sizeof (_info->_size));
    }
    if(_new_data.size())
    {
        _info->_msg += _new_data;
        _info->_size -= _new_data.size();
    }

    if(_info->_size > 0)
    {

        delete this;
        return;
    }
    _info->_is_recved = true;
    emit recved_data();
    delete this;
}


TaskRecvMsg::~TaskRecvMsg()
{

}

TaskRecvMsg::TaskRecvMsg(WorkInfo *info,QByteArray &new_data):
    _info(info), _new_data(new_data)
{

}
