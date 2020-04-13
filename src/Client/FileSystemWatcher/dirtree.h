#ifndef DIRTREE_H
#define DIRTREE_H

#include <QString>
#include <QDateTime>

struct DirTree
{
    QString name;
    QDateTime last_modify;
    QList<DirTree> dirs;
    QList<QString> files;

    void remove_file(const QString &path)
    {
        auto dir = find_dir_with_file(path);
        if(dir)
        {
            dir->files.removeOne(path);
        }
    }

    DirTree* find_dir(const QString &path)
    {
        if(path == name + '/')
        {
            return this;
        }
        if(path.indexOf(name) != -1)
        {
            for(auto &dir : dirs)
            {
                if(path.indexOf(dir.name) != -1)
                {
                    return find_dir(path);
                }
            }
        }
        return nullptr;
    }

    DirTree* find_dir_with_file(const QString &path)
    {
        auto dir_path = path.mid(0,path.indexOf(path.split('/').last()));
        auto dir = find_dir(dir_path);
        if(dir->files.end() == std::find(dir->files.begin(),dir->files.end(),path))
        {
            return nullptr;
        }
        return dir;
    }
};

#endif // DIRTREE_H
