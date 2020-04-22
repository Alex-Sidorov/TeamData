#include "workerserverdatabase.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariantList>

const char* WorkerServerDataBase::TYPE_DATA_BASE = "QSQLITE";
const char* WorkerServerDataBase::DEFAULT_NAME_DATA_BASE = "data.sqlite";

const char* WorkerServerDataBase::INSERT_USER_REQUEST = "INSERT INTO users (name) VALUES (:name);";
const char* WorkerServerDataBase::DELETE_USER_REQUEST = "DELETE FROM users WHERE name = :name;";
const char* WorkerServerDataBase::SELECT_USER_REQUEST = "SELECT name FROM users;";
const char* WorkerServerDataBase::SELECT_ANY_USER_REQUEST = "SELECT name FROM users WHERE name = :name;";

const char* WorkerServerDataBase::INSERT_DIR_REQUEST = "INSERT INTO dirs (name,path) VALUES (:name,:path);";
const char* WorkerServerDataBase::DELETE_DIR_REQUEST = "DELETE FROM dirs WHERE name = :name;";
const char* WorkerServerDataBase::SELECT_DIR_REQUEST = "SELECT path FROM dirs  WHERE name = :name;";

const char* WorkerServerDataBase::INSERT_FILES_REQUEST = "INSERT INTO files (name,path,created_data,last_modified_data,size) "
                                                         "VALUES (:name,:path,:created_data,:last_modified_data,:size);";
const char* WorkerServerDataBase::DELETE_FILES_REQUEST = "DELETE FROM files WHERE name = :name;";
const char* WorkerServerDataBase::SELECT_FILES_REQUEST = "SELECT path,created_data,last_modified_data,size FROM files WHERE name = :name;";

QStringList WorkerServerDataBase::get_all_user()const
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

bool WorkerServerDataBase::insert_user(const QString &user)
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

bool WorkerServerDataBase::delete_user(const QString &user)
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

bool WorkerServerDataBase::is_user(const QString &user)
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

bool WorkerServerDataBase::insert_data_dir_user(const QString &user,const QStringList &dirs)
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

bool WorkerServerDataBase::delete_data_dir_user(const QString &user)
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

WorkerServerDataBase::DirsPath WorkerServerDataBase::get_data_dir_user(const QString &user)
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

bool WorkerServerDataBase::insert_data_files_user(const QString &user,const WorkerServerDataBase::FileMetaData &data)
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

bool WorkerServerDataBase::delete_data_files_user(const QString &user)
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

WorkerServerDataBase::FileMetaData WorkerServerDataBase::get_data_files_user(const QString &user)
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

WorkerServerDataBase::WorkerServerDataBase():
    _base(QSqlDatabase::addDatabase(TYPE_DATA_BASE))
{
    _base.setDatabaseName(DEFAULT_NAME_DATA_BASE);
    _base.open();
}

WorkerServerDataBase::~WorkerServerDataBase()
{
    _base.close();
}
