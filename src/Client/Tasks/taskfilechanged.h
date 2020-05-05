#ifndef TASKFILECHANGED_H
#define TASKFILECHANGED_H

#include "ActiveObject/abstracttask.h"
#include "Workers/workermetadata.h"

#include <QObject>
#include <QMutex>
#include <QMutexLocker>

namespace TasksClient
{
    class TaskFileChanged : public QObject, public ActiveObject::AbstractTask
    {
        Q_OBJECT

        using MDD = WorkMetaDataOnClient::WorkerMetaData::MetaDataDir;

    signals:
        void complete_task();

    public:
        void run_process() override;

        void exec();

        TaskFileChanged(MDD *meta_data, MDD *present_meta_data, const QString &path, const QString &root, QMutex *mutex = nullptr);
        virtual ~TaskFileChanged()  override;

    private:
        QString _root;
        QString _path;

        MDD *_meta_data;
        MDD *_present_meta_data;

        QMutex *_mutex;
    };
}

#endif // TASKFILECHANGED_H
