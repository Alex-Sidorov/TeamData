#ifndef WORKERUSERS_H
#define WORKERUSERS_H

#include <QString>
#include <QSettings>
#include <QStringList>

#include "workerclientdatabase.h"

class Settings
{
public:

    Settings();
    virtual ~Settings();

    bool set_self_addr(const QString &addr);
    bool set_self_port(quint16 port);

    QString get_self_addr()const;
    quint16 get_self_port()const;

    QString read_self_addr()const;
    quint16 read_self_port()const;

    bool set_serv_addr(const QString &addr);
    bool set_serv_port(quint16 port);

    QString get_serv_addr()const;
    quint16 get_serv_port()const;

    QString read_serv_addr()const;
    quint16 read_serv_port()const;

    bool set_path(const QString &path);

    QString get_path()const;

    QString read_path()const;

    bool set_name(const QString &name);

    QString get_name()const;

    QString read_name()const;

    bool read_settings(const QString &name_file = NAME_FILE_SETTINGS);

    bool add_user(const QString &user);
    QStringList get_users()const;

    bool change_data_dir_user(const QString &user,const QStringList &dirs);
    WorkerClientDataBase::DirsPath get_data_dir_user(const QString &user);

    bool change_data_files_user(const QString &user, const WorkerClientDataBase::FileMetaData &data);
    WorkerClientDataBase::FileMetaData get_data_files_user(const QString &user);

    bool insert_task_user(const QString &user, const QStringList &files, const QStringList &local_files, const QStringList &dates);
    bool update_task_user(const QString &user,const QString &file, const QString &date);
    bool delete_all_task_user(const QString &user);
    bool delete_task_user(const QString &user, const QStringList &files);
    WorkerClientDataBase::Tasks get_all_task_user(const QString &user)const;
    WorkerClientDataBase::UsersTasks get_all_task_users()const;

    bool insert_addr_info_user(const QString &user,const QString &addr, quint16 port);
    bool delete_addr_info_user(const QString &user);
    QPair<QString,quint16> get_addr_info_user(const QString &user);

private:
    QString _self_addr;
    quint16 _self_port;

    QString _serv_addr;
    quint16 _serv_port;

    QString _name;

    QString _path;

    QSettings _settings;

    static const char* NAME_FILE_SETTINGS;

    static const char* NAME_GROUP_SERVER_SETTINGS;
    static const char* SETTINGS_VALUE_ADDRESS_SERVER;
    static const char* SETTINGS_VALUE_PORT_SERVER;

    static const char* NAME_GROUP_CLIENT_SETTINGS;
    static const char* SETTINGS_VALUE_ADDRESS_CLIENT;
    static const char* SETTINGS_VALUE_PORT_CLIENT;
    static const char* SETTINGS_VALUE_NAME;
    static const char* SETTINGS_VALUE_WORKDIR;
};

#endif // WORKERUSERS_H
