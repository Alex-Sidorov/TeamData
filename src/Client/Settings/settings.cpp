#include "settings.h"

#include <QFileInfo>

using namespace SettingsClient;

const char* Settings::NAME_FILE_SETTINGS = "settings.conf";

const char* Settings::NAME_GROUP_SERVER_SETTINGS =      "server";
const char* Settings::SETTINGS_VALUE_ADDRESS_SERVER =   "addr";
const char* Settings::SETTINGS_VALUE_PORT_SERVER =      "port";

const char* Settings::NAME_GROUP_CLIENT_SETTINGS =      "client";
const char* Settings::SETTINGS_VALUE_ADDRESS_CLIENT =   "addr";
const char* Settings::SETTINGS_VALUE_PORT_CLIENT =      "port";
const char* Settings::SETTINGS_VALUE_NAME =             "name";
const char* Settings::SETTINGS_VALUE_WORKDIR =          "path";


bool Settings::set_self_addr(const QString &addr)
{
    if(_settings.isWritable())
    {
        auto key = QString(NAME_GROUP_CLIENT_SETTINGS) +
                        '/' +
                        SETTINGS_VALUE_ADDRESS_CLIENT;

        _settings.setValue(key,addr);
        _self_addr = addr;
        return true;
    }
    return false;
}

bool Settings::set_self_port(quint16 port)
{
    if(_settings.isWritable())
    {
        auto key = QString(NAME_GROUP_CLIENT_SETTINGS) +
                        '/' +
                        SETTINGS_VALUE_PORT_CLIENT;

        _settings.setValue(key,port);
        _self_port = port;
        return true;
    }
    return false;
}

bool Settings::set_serv_addr(const QString &addr)
{
    if(_settings.isWritable())
    {
        auto key = QString(NAME_GROUP_SERVER_SETTINGS) +
                        '/' +
                        SETTINGS_VALUE_ADDRESS_SERVER;

        _settings.setValue(key,addr);
        _serv_addr = addr;
        return true;
    }
    return false;
}

bool Settings::set_serv_port(quint16 port)
{
    if(_settings.isWritable())
    {
        auto key = QString(NAME_GROUP_SERVER_SETTINGS) +
                        '/' +
                        SETTINGS_VALUE_PORT_SERVER;

        _settings.setValue(key,port);
        _serv_port = port;
        return true;
    }
    return false;
}

bool Settings::set_path(const QString &path)
{
    if(_settings.isWritable())
    {
        auto key = QString(NAME_GROUP_CLIENT_SETTINGS) +
                        '/' +
                        SETTINGS_VALUE_WORKDIR;

        _settings.setValue(key,path);
        _path = path;
        return true;
    }
    return false;
}

bool Settings::set_name(const QString &name)
{
    if(_settings.isWritable())
    {
        auto key = QString(NAME_GROUP_CLIENT_SETTINGS) +
                        '/' +
                        SETTINGS_VALUE_NAME;

        _settings.setValue(key,name);
        _name = name;
        return true;
    }
    return false;
}

QString Settings::get_self_addr()const
{
    return _self_addr;
}

quint16 Settings::get_self_port()const
{
    return _self_port;
}

QString Settings::get_serv_addr()const
{
    return _serv_addr;
}

quint16 Settings::get_serv_port()const
{
    return _serv_port;
}


QString Settings::get_path()const
{
    return _path;
}

QString Settings::get_name()const
{
    return _name;
}

QString Settings::read_self_addr()const
{
    auto key = QString(NAME_GROUP_CLIENT_SETTINGS) +
                    '/' +
                    SETTINGS_VALUE_ADDRESS_CLIENT;
    return _settings.value(key,"").toString();
}

quint16 Settings::read_self_port()const
{
    auto key = QString(NAME_GROUP_CLIENT_SETTINGS) +
                '/' +
                SETTINGS_VALUE_PORT_CLIENT;
    return  static_cast<quint16>(_settings.value(key,0).toInt());
}

QString Settings::read_serv_addr()const
{
    auto key = QString(NAME_GROUP_SERVER_SETTINGS) +
                    '/' +
                    SETTINGS_VALUE_ADDRESS_SERVER;
    return _settings.value(key,"").toString();
}

quint16 Settings::read_serv_port()const
{
    auto key = QString(NAME_GROUP_SERVER_SETTINGS) +
                '/' +
                SETTINGS_VALUE_PORT_SERVER;
    return static_cast<quint16>(_settings.value(key,0).toInt());
}

QString Settings::read_path()const
{
    auto key = QString(NAME_GROUP_CLIENT_SETTINGS) +
                    '/' +
                    SETTINGS_VALUE_WORKDIR;
    return _settings.value(key,"").toString();
}

QString Settings::read_name()const
{
    auto key = QString(NAME_GROUP_CLIENT_SETTINGS) +
                    '/' +
                    SETTINGS_VALUE_NAME;
    return _settings.value(key,"").toString();
}

bool Settings::read_settings(const QString &name_file)
{
    if(_settings.fileName() != name_file)
    {
        _settings.setPath(QSettings::IniFormat,QSettings::UserScope,name_file);
    }

    auto self_addr = read_self_addr();
    if(self_addr.isEmpty())
    {
        return false;
    }

    quint16 self_port = read_self_port();
    if(!self_port)
    {
        return false;
    }

    auto serv_addr = read_serv_addr();
    if(serv_addr.isEmpty())
    {
        return false;
    }

    quint16 serv_port = read_serv_port();
    if(!serv_port)
    {
        return false;
    }

    auto name = read_name();
    if(name.isEmpty())
    {
        return false;
    }

    auto path = read_path();
    if(path.isEmpty())
    {
        return false;
    }

    _self_addr = self_addr;
    _self_port = self_port;
    _serv_addr = serv_addr;
    _serv_port = serv_port;
    _name = name;
    _path = path;
    return true;
}

bool Settings::add_user(const QString &user)
{
    bool res = false;
    auto connection_name = DBWorker::get_new_name_connection();
    {
        res = DBWorker(connection_name).insert_user(user);
    }
    DBWorker::remove_connection(connection_name);
    return res;
}

QStringList Settings::get_users()const
{
    QStringList res;
    auto connection_name = DBWorker::get_new_name_connection();
    {
        res = DBWorker(connection_name).get_all_user();
    }
    DBWorker::remove_connection(connection_name);
    return res;
}

bool Settings::change_data_dir_user(const QString &user,const QStringList &dirs)
{
    bool res = false;
    auto connection_name = DBWorker::get_new_name_connection();
    {
        DBWorker worker(connection_name);
        if(worker.delete_data_dir_user(user))
        {
            if(worker.insert_data_dir_user(user,dirs))
            {
                res = true;
            }
            res = false;
        }
    }
    DBWorker::remove_connection(connection_name);
    return res;

}
DataBaseWork::WorkerClientDataBase::DirsPath Settings::get_data_dir_user(const QString &user)
{
    DBWorker::DirsPath res;
    auto connection_name = DBWorker::get_new_name_connection();
    {
        res = DBWorker(connection_name).get_data_dir_user(user);
    }
    DBWorker::remove_connection(connection_name);
    return res;
}

bool Settings::change_data_files_user(const QString &user, const DBWorker::FileMetaData &files)
{
    bool res = false;
    auto connection_name = DBWorker::get_new_name_connection();
    {
        DBWorker worker(connection_name);
        if(worker.delete_data_files_user(user))
        {
            if(worker.insert_data_files_user(user,files))
            {
                res = true;
            }
            res = false;
        }
    }
    DBWorker::remove_connection(connection_name);
    return res;
}

DataBaseWork::WorkerClientDataBase::FileMetaData Settings::get_data_files_user(const QString &user)
{
    DBWorker::FileMetaData res;
    auto connection_name = DBWorker::get_new_name_connection();
    {
        res = DBWorker(connection_name).get_data_files_user(user);
    }
    DBWorker::remove_connection(connection_name);
    return res;
}

bool Settings::insert_task_user(const QString &user,const QStringList &files, const QStringList &local_files, const QStringList &dates)
{
    bool res = false;
    auto connection_name = DBWorker::get_new_name_connection();
    {
        res = DBWorker(connection_name).insert_task_user(user,files,local_files,dates);
    }
    DBWorker::remove_connection(connection_name);
    return res;
}

bool Settings::update_task_user(const QString &user,const QString &file, const QString &date)
{
    bool res = false;
    auto connection_name = DBWorker::get_new_name_connection();
    {
        res = DBWorker(connection_name).update_task_user(user,file,date);
    }
    DBWorker::remove_connection(connection_name);
    return res;
}

bool Settings::delete_all_task_user(const QString &user)
{
    bool res = false;
    auto connection_name = DBWorker::get_new_name_connection();
    {
        res = DBWorker(connection_name).delete_all_task_user(user);
    }
    DBWorker::remove_connection(connection_name);
    return res;
}

bool Settings::delete_task_user(const QString &user, const QStringList &files)
{
    bool res = false;
    auto connection_name = DBWorker::get_new_name_connection();
    {
        res = DBWorker(connection_name).delete_task_user(user,files);
    }
    DBWorker::remove_connection(connection_name);
    return res;
}

DataBaseWork::WorkerClientDataBase::Tasks Settings::get_all_task_user(const QString &user)const
{
    DBWorker::Tasks res;
    auto connection_name = DBWorker::get_new_name_connection();
    {
        res = DBWorker(connection_name).get_all_task_user(user);
    }
    DBWorker::remove_connection(connection_name);
    return res;
}

DataBaseWork::WorkerClientDataBase::UsersTasks Settings::get_all_task_users()const
{
    DBWorker::UsersTasks res;
    auto connection_name = DBWorker::get_new_name_connection();
    {
        res = DBWorker(connection_name).get_all_task_users();
    }
    DBWorker::remove_connection(connection_name);
    return res;
}

bool Settings::insert_addr_info_user(const QString &user,const QString &addr, quint16 port)
{
    bool res = false;
    auto connection_name = DBWorker::get_new_name_connection();
    {
        DBWorker worker(connection_name);
        if(worker.is_user_info(user))
        {
            res = worker.change_addr_user(user,addr) && worker.change_port_user(user,port);
        }
        else
        {
            res = worker.insert_addr_info_user(user,addr,port);
        }
    }
    DBWorker::remove_connection(connection_name);
    return res;

}

bool Settings::delete_addr_info_user(const QString &user)
{
    bool res= false;
    auto connection_name = DBWorker::get_new_name_connection();
    {
        res = DBWorker(connection_name).delete_addr_info_user(user);
    }
    DBWorker::remove_connection(connection_name);
    return res;
}

QPair<QString,quint16> Settings::get_addr_info_user(const QString &user)
{
    QPair<QString,quint16> res;
    auto connection_name = DBWorker::get_new_name_connection();
    {
        res = DBWorker(connection_name).get_addr_info_user(user);
    }
    DBWorker::remove_connection(connection_name);
    return res;
}

Settings::Settings():
    _self_port(0),
    _serv_port(0),
    _settings(NAME_FILE_SETTINGS,QSettings::IniFormat)
{
    QFileInfo info(NAME_FILE_SETTINGS);
    if(!info.isFile())
    {
        set_name("");
        set_path("");
        set_serv_addr("");
        set_serv_port(0);
        set_self_addr("");
        set_self_port(0);
    }

}


Settings::~Settings()
{}
