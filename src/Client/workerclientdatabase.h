#ifndef WORKERSERVERDATABASE_H
#define WORKERSERVERDATABASE_H

#include <QSqlDatabase>
#include <QStringList>
#include <QMap>

class WorkerClientDataBase
{
public:

    using FileCharacteristics = std::tuple<quint64,QString,QString>;
    using FileMetaData = QMap<QString,FileCharacteristics>;
    using DirsPath = QStringList;
    using Tasks = QStringList;
    using UsersTasks = QMap<QString,Tasks>;


    WorkerClientDataBase();
    virtual ~WorkerClientDataBase();

    bool insert_user(const QString &user);
    bool delete_user(const QString &user);
    bool is_user(const QString &user);
    QStringList get_all_user()const;

    bool insert_data_dir_user(const QString &user,const QStringList &dirs);
    bool delete_data_dir_user(const QString &user);
    DirsPath get_data_dir_user(const QString &user);

    bool insert_data_files_user(const QString &user, const FileMetaData &data);
    bool delete_data_files_user(const QString &user);
    FileMetaData get_data_files_user(const QString &user);

    bool insert_task_user(const QString &user,const QStringList &files);
    bool delete_task_user(const QString &user);
    Tasks get_task_user(const QString &user)const;
    UsersTasks get_all_task_user()const;

private:
    QSqlDatabase _base;

    static const char* DEFAULT_NAME_DATA_BASE;
    static const char* TYPE_DATA_BASE;

    static const char* INSERT_USER_REQUEST;
    static const char* DELETE_USER_REQUEST;
    static const char* SELECT_USER_REQUEST;
    static const char* SELECT_ANY_USER_REQUEST;

    static const char* INSERT_DIR_REQUEST;
    static const char* DELETE_DIR_REQUEST;
    static const char* SELECT_DIR_REQUEST;

    static const char* INSERT_FILES_REQUEST;
    static const char* DELETE_FILES_REQUEST;
    static const char* SELECT_FILES_REQUEST;

    static const char* INSERT_TASK_REQUEST;
    static const char* DELETE_TASK_REQUEST;
    static const char* SELECT_TASK_REQUEST;
    static const char* SELECT_ANY_TASK_REQUEST;
};

#endif // WORKERSERVERDATABASE_H
