#include "workerclientdatabase.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariantList>

const char* WorkerClientDataBase::TYPE_DATA_BASE = "QSQLITE";
const char* WorkerClientDataBase::DEFAULT_NAME_DATA_BASE = "data.sqlite";

const char* WorkerClientDataBase::INSERT_USER_REQUEST = "INSERT INTO users (name) VALUES (:name);";
const char* WorkerClientDataBase::DELETE_USER_REQUEST = "DELETE FROM users WHERE name = :name;";
const char* WorkerClientDataBase::SELECT_USER_REQUEST = "SELECT name FROM users;";
const char* WorkerClientDataBase::SELECT_ANY_USER_REQUEST = "SELECT name FROM users WHERE name = :name;";

const char* WorkerClientDataBase::INSERT_DIR_REQUEST = "INSERT INTO dirs (name,path) VALUES (:name,:path);";
const char* WorkerClientDataBase::DELETE_DIR_REQUEST = "DELETE FROM dirs WHERE name = :name;";
const char* WorkerClientDataBase::SELECT_DIR_REQUEST = "SELECT path FROM dirs  WHERE name = :name;";

const char* WorkerClientDataBase::INSERT_FILES_REQUEST = "INSERT INTO files (name,path,created_data,last_modified_data,size) "
                                                         "VALUES (:name,:path,:created_data,:last_modified_data,:size);";
const char* WorkerClientDataBase::DELETE_FILES_REQUEST = "DELETE FROM files WHERE name = :name;";
const char* WorkerClientDataBase::SELECT_FILES_REQUEST = "SELECT path,created_data,last_modified_data,size FROM files WHERE name = :name;";

const char* WorkerClientDataBase::INSERT_TASK_REQUEST = "INSERT INTO tasks (name,file) VALUES (:name,:file);";
const char* WorkerClientDataBase::DELETE_TASK_REQUEST = "DELETE FROM tasks WHERE name = :name;";
const char* WorkerClientDataBase::SELECT_ANY_TASK_REQUEST = "SELECT file FROM tasks  WHERE name = :name;";
const char* WorkerClientDataBase::SELECT_TASK_REQUEST = "SELECT * FROM tasks;";

QStringList WorkerClientDataBase::get_all_user()const
{
    QStringList res;
    QSqlQuery query;
    query.prepare(SELECT_USER_REQUEST);
    if(_base.isOpen() && query.exec())
    {
        while(query.next())
        {
            res += query.value("name").toString();
        }
    }
    return res;
}

bool WorkerClientDataBase::insert_user(const QString &user)
{
    QSqlQuery query;
    query.prepare(INSERT_USER_REQUEST);
    query.bindValue(":name",user);
    if(!_base.isOpen() || !query.exec())
    {
        return false;
    }
    return true;
}

bool WorkerClientDataBase::delete_user(const QString &user)
{
    QSqlQuery query;
    query.prepare(DELETE_USER_REQUEST);
    query.bindValue(":name",user);
    if(!_base.isOpen() || !is_user(user) || !query.exec())
    {
        return false;
    }
    return true;
}

bool WorkerClientDataBase::is_user(const QString &user)
{
    QSqlQuery query;
    query.prepare(SELECT_ANY_USER_REQUEST);
    query.bindValue(":name",user);
    if(!_base.isOpen() || !query.exec())
    {
        return false;
    }
    else
    {
        if(!query.next())
        {
            return false;
        }
        return true;
    }
}

bool WorkerClientDataBase::insert_data_dir_user(const QString &user,const QStringList &dirs)
{
    if(_base.isOpen() && is_user(user))
    {
        _base.transaction();
        QSqlQuery query;
        query.prepare(INSERT_DIR_REQUEST);
        for(auto &dir : dirs)
        {
            query.bindValue(":name",user);
            query.bindValue(":path",dir);
            if(!query.exec())
            {
                _base.rollback();
                return false;
            }
        }
        _base.commit();
        return true;
    }
    return false;
}

bool WorkerClientDataBase::delete_data_dir_user(const QString &user)
{
    if(_base.isOpen())
    {
        _base.transaction();
        QSqlQuery query;
        query.prepare(DELETE_DIR_REQUEST);
        query.bindValue(":name",user);
        if(!query.exec())
        {
            _base.rollback();
            return false;
        }
        _base.commit();
        return true;
    }
    return false;
}

WorkerClientDataBase::DirsPath WorkerClientDataBase::get_data_dir_user(const QString &user)
{
    QStringList res;
    QSqlQuery query;
    query.prepare(SELECT_DIR_REQUEST);
    query.bindValue(":name",user);
    if(_base.isOpen() && query.exec())
    {
        while(query.next())
        {
            res += query.value("path").toString();
        }
    }
    return res;
}

bool WorkerClientDataBase::insert_data_files_user(const QString &user,const WorkerClientDataBase::FileMetaData &data)
{
    if(_base.isOpen() && is_user(user))
    {
        _base.transaction();
        QSqlQuery query;
        query.prepare(INSERT_FILES_REQUEST);
        for(auto it = data.begin(); it != data.end(); it++)
        {
            query.bindValue(":name",user);
            query.bindValue(":path",it.key());
            query.bindValue(":created_data",std::get<2>(it.value()));
            query.bindValue(":last_modified_data",std::get<1>(it.value()));
            query.bindValue(":size",QString::number(std::get<0>(it.value())));

            if(!query.exec())
            {
                _base.rollback();
                return false;
            }
        }
        _base.commit();
        return true;
    }
    return false;
}

bool WorkerClientDataBase::delete_data_files_user(const QString &user)
{
    if(_base.isOpen())
    {
        _base.transaction();
        QSqlQuery query;
        query.prepare(DELETE_FILES_REQUEST);
        query.bindValue(":name",user);
        if(!query.exec())
        {
            _base.rollback();
            return false;
        }
        _base.commit();
        return true;
    }
    return false;
}

WorkerClientDataBase::FileMetaData WorkerClientDataBase::get_data_files_user(const QString &user)
{
    FileMetaData res;
    QSqlQuery query;
    query.prepare(SELECT_FILES_REQUEST);
    query.bindValue(":name",user);
    if(_base.isOpen() && query.exec())
    {
        while(query.next())
        {
            quint64 size = static_cast<quint64>(query.value("size").toString().toDouble());
            auto created_data = query.value("created_data").toString();
            auto last_modified_data = query.value("last_modified_data").toString();
            FileCharacteristics data = std::make_tuple(size,last_modified_data,created_data);
            res.insert(user,data);
        }
    }
    return res;
}

bool WorkerClientDataBase::insert_task_user(const QString &user,const QStringList &files)
{
    if(_base.isOpen() && is_user(user))
    {
        _base.transaction();
        QSqlQuery query;
        query.prepare(INSERT_TASK_REQUEST);
        for(auto &file : files)
        {
            query.bindValue(":name",user);
            query.bindValue(":file",file);
            if(!query.exec())
            {
                _base.rollback();
                return false;
            }
        }
        _base.commit();
        return true;
    }
    return false;
}

bool WorkerClientDataBase::delete_task_user(const QString &user)
{
    if(_base.isOpen())
    {
        _base.transaction();
        QSqlQuery query;
        query.prepare(DELETE_TASK_REQUEST);
        query.bindValue(":name",user);
        if(!query.exec())
        {
            _base.rollback();
            return false;
        }
        _base.commit();
        return true;
    }
    return false;
}

WorkerClientDataBase::Tasks WorkerClientDataBase::get_task_user(const QString &user)const
{
    Tasks res;
    QSqlQuery query;
    query.prepare(SELECT_ANY_TASK_REQUEST);
    query.bindValue(":name",user);
    if(_base.isOpen() && query.exec())
    {
        while(query.next())
        {
            res += query.value("file").toString();
        }
    }
    return res;
}

QMap<QString,QStringList> WorkerClientDataBase::get_all_task_user()const
{
    QMap<QString,QStringList> res;
    QSqlQuery query;
    query.prepare(SELECT_TASK_REQUEST);
    if(_base.isOpen() && query.exec())
    {
        while(query.next())
        {
            auto user = query.value("name").toString();
            res[user].append(query.value("file").toString());
        }
    }
    return res;
}

WorkerClientDataBase::WorkerClientDataBase():
    _base(QSqlDatabase::addDatabase(TYPE_DATA_BASE))
{
    _base.setDatabaseName(DEFAULT_NAME_DATA_BASE);
    _base.open();
}

WorkerClientDataBase::~WorkerClientDataBase()
{
    _base.close();
}
