#include "tasksendfile.h"

TaskSendFile::TaskSendFile(QFile *file, PROXY *proxy, uint32_t MTU):
    _file(file),
    _proxy(proxy),
    _MTU(MTU),
    _is_sended(false)
{}

TaskSendFile::~TaskSendFile()
{}

void TaskSendFile::run_process()
{
    if(!_file || !_file->isOpen())
    {
        if(_file)
        {
            delete _file;
        }
        delete this;
        return;
    }
    QByteArray data;
    if(!_is_sended)
    {
        qint32 size = _file->size();
        data = Client::IntToArray(size);
        _is_sended = true;
        data += _file->read(_MTU - sizeof (size));
    }
    else
    {
        data += _file->read(_MTU);
    }

    emit send_data(data);

    if(_file->atEnd())
    {
        _file->close();
        delete _file;
        delete this;
    }
    else
    {
        _proxy->push(this);
    }
}
