#ifndef TASKRECVMSG_H
#define TASKRECVMSG_H

#include <QObject>

#include <atomic>
#include <map>

#include <ActiveObject/abstracttask.h>
#include <ActiveObject/proxyactiveobject.h>
#include <BaseClient/base_client.h>

using DataTransfer::BaseClient;

class TaskRecvMsg : public QObject, public ActiveObject::AbstractTask
{
    Q_OBJECT

signals:
    void recved_data();
public:

    struct WorkInfo
    {
        WorkInfo():_size(0), _is_recved(false){}
        void clear()
        {
            _size = 0;
            _is_recved = false;
            _msg.clear();
        }
        QByteArray _msg;
        qint32 _size;
        bool _is_recved;
    };

    void run_process() override;

    TaskRecvMsg(WorkInfo *_info,QByteArray &new_data);
    virtual ~TaskRecvMsg()  override;

private:
    WorkInfo *_info;
    QByteArray _new_data;
};

#endif // TASKRECVMSG_H
