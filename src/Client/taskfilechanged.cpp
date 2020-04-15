#include "taskfilechanged.h"

#include <QFileInfo>
#include "FileSystemWatcher/filesystem_informer.h"

using fsi = FileSystemWatcher::FileSystemInformer;

void TaskFileChanged::run_process()
{
    exec();
    emit complete_task();
    delete this;
}

void TaskFileChanged::exec()
{
    QMutexLocker lock(_mutex);
    QFileInfo info(_path);
    if(info.isFile())
    {
        QStringList list{_path};
        auto size_files = fsi::get_size_files(list);
        auto date_last_modified_files = fsi::get_date_last_modified_files(list);
        auto date_create_files = fsi::get_date_created_files(list);
        _meta_data->second[_path] = std::make_tuple(size_files[0],date_create_files[0],date_last_modified_files[0]);
        auto temp = _path.mid(_root.size());
        _present_meta_data->second[temp] = std::make_tuple(size_files[0],date_create_files[0],date_last_modified_files[0]);
    }
    else
    {
        _meta_data->second.remove(_path);
        _present_meta_data->second.remove(_path.mid(_root.size()));
    }
}

TaskFileChanged::TaskFileChanged(MDD *meta_data, MDD *present_meta_data, const QString &path, const QString &root, QMutex *mutex):
    _root(root), _path(path), _meta_data(meta_data), _present_meta_data(present_meta_data), _mutex(mutex)
{

}

TaskFileChanged::~TaskFileChanged()
{
}
