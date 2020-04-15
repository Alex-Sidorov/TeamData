#include "taskdirchanged.h"

#include <QFileInfo>
#include "FileSystemWatcher/filesystem_informer.h"

using fsi = FileSystemWatcher::FileSystemInformer;

void TaskDirChanged::run_process()
{
    emit complete_task( exec() );
    delete this;
}

bool TaskDirChanged::exec()
{
    QMutexLocker lock(_mutex);
    bool is_changed = false;

    auto dirs = fsi::get_terminal_directories(_root);
    if(dirs != _meta_data->first)
    {
        is_changed = true;
        _meta_data->first = dirs;
        WorkerMetaData::remove_root_path(_root,dirs);
        _present_meta_data->first = dirs;
        add_dirs_path(dirs);
    }

    auto files = fsi::get_files(_path);
    auto new_files = get_added_files(files);
    auto removed_files = get_removed_files(files,_path);

    if(new_files.size())
    {
        is_changed = true;
        _watcher->addPaths(new_files);
        auto size_files = fsi::get_size_files(new_files);
        auto date_last_modified_files = fsi::get_date_last_modified_files(new_files);
        auto date_create_files = fsi::get_date_created_files(new_files);
        for(int i = 0; i < new_files.size(); i++)
        {
            _meta_data->second.insert(new_files[i],std::make_tuple(size_files[i],date_create_files[i],date_last_modified_files[i]));
            _present_meta_data->second.insert(new_files[i].mid(_root.size()),std::make_tuple(size_files[i],date_create_files[i],date_last_modified_files[i]));
        }
    }

    if(removed_files.size())
    {
        is_changed = true;
        for(auto &file : removed_files)
        {
            _meta_data->second.remove(file);
            _present_meta_data->second.remove(file.mid(_root.size()));
        }
    }
    return is_changed;
}

QStringList TaskDirChanged::get_removed_files(const QStringList &scan_files, const QString &path)const
{
    QStringList result;
    auto it = _meta_data->second.begin();
    while(it != _meta_data->second.end())
    {
        if(it.key().indexOf(path) != -1 && it.key()[path.size()] == '/' && scan_files.indexOf(it.key()) == -1)
        {
            result.append(it.key());
        }
        ++it;
    }
    return result;
}

QStringList TaskDirChanged::get_added_files(const QStringList &scan_files)const
{
    auto files = scan_files;
    auto it = _meta_data->second.begin();
    while(it != _meta_data->second.end())
    {
        files.removeOne(it.key());
        ++it;
    }
    return files;
}

QStringList TaskDirChanged::get_removed_folders(const QStringList &scan_dirs, const QString &path)const
{
    QStringList result;
    for(auto &dir : _meta_data->first)
    {
        if(dir.indexOf(path) != -1 && dir != path && scan_dirs.indexOf(dir) == -1)
        {
            result.append(dir);
        }
    }
    return result;
}

QStringList TaskDirChanged::get_added_folders(const QStringList &scan_dirs)const
{
    auto dirs = scan_dirs;
    for(auto &dir : _meta_data->first)
    {
        dirs.removeOne(dir);
    }
    return dirs;
}

void TaskDirChanged::add_dirs_path(QStringList &dirs)
{
    for(auto &dir:dirs)
    {
        auto path = dir.split('/');
        path.removeAll("");
        auto temp = _root + '/';
        for (int i = 0; i < path.size(); i++)
        {
            temp += path[i] + '/';
            if(!(i % 2 == 0))
            {
                _watcher->addPath(temp);
            }
        }
    }
}

TaskDirChanged::TaskDirChanged(MDD *meta_data, MDD *present_meta_data, const QString &path, const QString &root, QFileSystemWatcher *watcher, QMutex *mutex):
    _root(root), _path(path), _meta_data(meta_data), _present_meta_data(present_meta_data), _watcher(watcher), _mutex(mutex)
{

}

TaskDirChanged::~TaskDirChanged()
{
}
