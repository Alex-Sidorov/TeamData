#ifndef FILESYSTEM_WORKER_H
#define FILESYSTEM_WORKER_H

#include <QStringList>
#include <QVector>

namespace FileSystemWatcher
{
    class FileSystemInformer
    {
    public:
        static QStringList parse_directory(const QString &path, uint16_t filter);
        static void remove_intermediary_directories(QStringList &directories);

        static QStringList get_terminal_directories(const QString &path);
        static QStringList get_full_directories(const QString &path);
        static QStringList get_full_without_dots_directories(const QString &path);
        static QStringList get_files(const QString &path);

        static QVector<qint64> get_size_files(const QStringList &files);
        static QVector<QString> get_date_created_files(const QStringList &files);
        static QVector<QString> get_date_last_modified_files(const QStringList &files);
    private:
        static constexpr const char* FORMAT_DATE = "dd.MM.yyyy hh:mm:ss";
    };
}




#endif // FILESYSTEM_WORKER_H
