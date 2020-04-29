#ifndef TASKRECVFILE_H
#define TASKRECVFILE_H

#include <QObject>
#include <QFile>

#include <ActiveObject/abstracttask.h>
#include <ActiveObject/proxyactiveobject.h>
#include <BaseClient/base_client.h>

using ActiveObject::ProxyActiveObject;

class TaskRecvFile : public QObject, public ActiveObject::AbstractTask
{
    Q_OBJECT

    using Client = DataTransfer::BaseClient;

signals:
    void recved_data();

public:

    struct WorkInfo
    {
        WorkInfo():_file(nullptr), _size(0), _is_recved(false){}
        void clear()
        {
            _file = nullptr;
            _size = 0;
            _is_recved = false;
        }
        QFile *_file;
        qint32 _size;
        bool _is_recved;
    };

    TaskRecvFile(WorkInfo *_info, QByteArray &new_data);
    virtual ~TaskRecvFile() override;

    void run_process() override;

private:
    WorkInfo *_info;
    QByteArray _new_data;
};

#endif // TASKRECVFILE_H
