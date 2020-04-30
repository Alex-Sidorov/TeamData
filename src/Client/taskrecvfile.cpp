#include "taskrecvfile.h"

TaskRecvFile::TaskRecvFile(WorkInfo *info,QByteArray &new_data):
    _info(info), _new_data(new_data)
{}

TaskRecvFile::~TaskRecvFile()
{}

void TaskRecvFile::run_process()
{
    if(!_info || !_info->_file)
    {
        delete this;
        return;
    }
    else if(!_info->_file->isOpen())
    {
        delete _info->_file;
        delete this;
        return;
    }
    else if(_new_data.isEmpty())
    {
        delete this;
        return;
    }

    if(!_info->_size)
    {
        _info->_is_recved = true;
        _info->_size = Client::ArrayToInt(_new_data);
        _new_data.remove(0,sizeof (_info->_size));
    }
    if(_new_data.size())
    {
        _info->_file->write(_new_data);
        _info->_size -= _new_data.size();
    }

    if(_info->_size > 0)
    {
        delete this;
        return;
    }

    _info->_file->close();
    delete _info->_file;

    emit recved_data();
    delete this;

}
