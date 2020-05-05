#ifndef TASKDIRCHANGED_H
#define TASKDIRCHANGED_H

#include "ActiveObject/abstracttask.h"
#include "Workers/workermetadata.h"

#include <QObject>
#include <QStringList>
#include <QMutex>
#include <QMutexLocker>
#include <QFileSystemWatcher>

namespace TasksClient
{
    class TaskDirChanged : public QObject, public ActiveObject::AbstractTask
    {
        Q_OBJECT

        using MDD = WorkMetaDataOnClient::WorkerMetaData::MetaDataDir;

    signals:
        void complete_task(bool);

    public:
        void run_process() override;

        bool exec();

        TaskDirChanged(MDD *meta_data,
                       MDD *present_meta_data,
                       const QString &path,
                       const QString &root,
                       QFileSystemWatcher *watcher,
                       QMutex *mutex = nullptr);

        virtual ~TaskDirChanged()  override;

    private:
        QString _root;
        QString _path;

        MDD *_meta_data;
        MDD *_present_meta_data;

        QFileSystemWatcher *_watcher;
        QMutex *_mutex;

        void add_dirs_path(QStringList &dirs);

        QStringList get_added_files(const QStringList &scan_files)const;
        QStringList get_removed_files(const QStringList &scan_files, const QString &path)const;
        QStringList get_added_folders(const QStringList &scan_files)const;
        QStringList get_removed_folders(const QStringList &scan_files, const QString &path)const;
    };
}

#endif // TASKDIRCHANGED_H
