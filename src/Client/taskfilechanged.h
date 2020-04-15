#ifndef TASKFILECHANGED_H
#define TASKFILECHANGED_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>

#include <ActiveObject/abstracttask.h>
#include <FileSystemWatcher/workermetadata.h>

class TaskFileChanged : public QObject, public ActiveObject::AbstractTask
{
    Q_OBJECT

    using MDD = WorkerMetaData::MetaDataDir;
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

#endif // TASKFILECHANGED_H
