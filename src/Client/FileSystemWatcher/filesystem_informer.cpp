#include "filesystem_informer.h"

#include <QDirIterator>
#include <QDateTime>

namespace fsw = FileSystemWatcher;

void fsw::FileSystemInformer::remove_intermediary_directories(QStringList &directories)
{
    if(!directories.isEmpty())
    {
        for(auto i = 0; i < directories.size() - 1;)
        {
            auto &cur = directories[i];
            auto &next = directories[i + 1];
            if(next.indexOf(cur) != -1)
            {
                directories.removeAt(i);
            }
            else
            {
                ++i;
            }
        }

    }
}

QStringList fsw::FileSystemInformer::parse_directory(const QString &path, uint16_t filter, bool is_sub_dir)
{
    QStringList data;
    QDirIterator it(path,static_cast<QDir::Filter>(filter), is_sub_dir ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags);
    while (it.hasNext())
    {
        data << it.next();
    }
    return data;
}

QStringList fsw::FileSystemInformer::get_terminal_directories(const QString &path)
{
    auto directories = parse_directory(path, QDir::Dirs | QDir::NoDotAndDotDot);
    remove_intermediary_directories(directories);
    return directories;
}

QStringList fsw::FileSystemInformer::get_full_directories(const QString &path)
{
    return parse_directory(path, QDir::Dirs);
}

QStringList fsw::FileSystemInformer::get_directory(const QString &path)
{
    return parse_directory(path, QDir::Dirs | QDir::NoDotAndDotDot,false);
}

QStringList fsw::FileSystemInformer::get_full_without_dots_directories(const QString &path)
{
    return parse_directory(path, QDir::Dirs | QDir::NoDotAndDotDot);
}

QStringList fsw::FileSystemInformer::get_files(const QString &path, bool is_sub_dir)
{
    return parse_directory(path,QDir::Files | QDir::NoDotAndDotDot, is_sub_dir);
}

QVector<qint64> fsw::FileSystemInformer::get_size_files(const QStringList &files)
{
    QVector<qint64> sizes;
    sizes.reserve((static_cast<int>(files.count())));
    foreach(auto item, files)
    {
        QFileInfo file(item);
        if(file.isFile())
        {
            sizes.push_back(file.size());
        }
    }
    return sizes;
}

QVector<QString> fsw::FileSystemInformer::get_date_created_files(const QStringList &files)
{
    QVector<QString> sizes;
    sizes.reserve((static_cast<int>(files.count())));
    foreach(auto item, files)
    {
        QFileInfo file(item);
        if(file.isFile())
        {
            sizes.push_back(file.birthTime().toString(FORMAT_DATE));
        }
    }
    return sizes;
}

QVector<QString> fsw::FileSystemInformer::get_date_last_modified_files(const QStringList &files)
{
    QVector<QString> sizes;
    sizes.reserve((static_cast<int>(files.count())));
    foreach(auto item, files)
    {
        QFileInfo file(item);
        if(file.isFile())
        {
            sizes.push_back(file.lastModified().toString(FORMAT_DATE));
        }
    }
    return sizes;
}
