#include "Workers/workerclientdatabase.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariantList>
#include <QThread>

using namespace DataBaseWork;

QMutex WorkerClientDataBase::_data_base_mutex(QMutex::Recursive);

const char* WorkerClientDataBase::TYPE_DATA_BASE = "QSQLITE";
const char* WorkerClientDataBase::DEFAULT_NAME_DATA_BASE = "data.sqlite";
const char* WorkerClientDataBase::DEFAULT_NAME_CONNECTION_DATA_BASE = "db_connection_";

const char* WorkerClientDataBase::INSERT_USER_REQUEST =
        "INSERT INTO users (name) VALUES (:name);";
const char* WorkerClientDataBase::DELETE_USER_REQUEST =
        "DELETE FROM users WHERE name = :name;";
const char* WorkerClientDataBase::SELECT_USER_REQUEST =
        "SELECT name FROM users;";
const char* WorkerClientDataBase::SELECT_ANY_USER_REQUEST =
        "SELECT name FROM users WHERE name = :name;";

const char* WorkerClientDataBase::INSERT_DIR_REQUEST =
        "INSERT INTO dirs (name,path) VALUES (:name,:path);";
const char* WorkerClientDataBase::DELETE_DIR_REQUEST =
        "DELETE FROM dirs WHERE name = :name;";
const char* WorkerClientDataBase::SELECT_DIR_REQUEST =
        "SELECT path FROM dirs  WHERE name = :name;";

const char* WorkerClientDataBase::INSERT_FILES_REQUEST =
        "INSERT INTO files (name,path,created_data,last_modified_data,size) "
        "VALUES (:name,:path,:created_data,:last_modified_data,:size);";
const char* WorkerClientDataBase::DELETE_FILES_REQUEST =
        "DELETE FROM files WHERE name = :name;";
const char* WorkerClientDataBase::SELECT_FILES_REQUEST =
        "SELECT path,created_data,last_modified_data,size FROM files WHERE name = :name;";

const char* WorkerClientDataBase::INSERT_TASK_REQUEST =
        "INSERT INTO tasks (name,file,local_file,last_modified) VALUES (:name,:file,:local_file,:last_modified);";
const char* WorkerClientDataBase::UPDATE_LAST_MODIFIED_TASK_FILE_REQUEST =
        "UPDATE tasks SET last_modified = :last_modified "
        "WHERE name = :name AND file = :file;";
const char* WorkerClientDataBase::DELETE_TASK_USER_REQUEST =
        "DELETE FROM tasks WHERE name = :name AND file = :file;";
const char* WorkerClientDataBase::DELETE_ALL_TASK_USER_REQUEST =
        "DELETE FROM tasks WHERE name = :name;";
const char* WorkerClientDataBase::SELECT_ANY_TASK_REQUEST =
        "SELECT file,local_file,last_modified FROM tasks  WHERE name = :name;";
const char* WorkerClientDataBase::SELECT_TASK_REQUEST =
        "SELECT * FROM tasks;";

const char* WorkerClientDataBase::INSERT_ADDR_INFO_USER_REQUEST =
        "INSERT INTO user_addr_info (name,port,addr) VALUES (:name,:port,:addr);";
const char* WorkerClientDataBase::DELETE_ADDR_INFO_REQUEST =
        "DELETE FROM user_addr_info WHERE name = :name;";
const char* WorkerClientDataBase::UPDATE_ADDR_USER_REQUEST =
        "UPDATE user_addr_info SET addr = :addr WHERE name = :name;";
const char* WorkerClientDataBase::UPDATE_PORT_USER_REQUEST =
        "UPDATE user_addr_info SET port = :port WHERE name = :name;";
const char* WorkerClientDataBase::SELECT_ANY_ADDR_INFO_REQUEST =
        "SELECT addr, port FROM user_addr_info WHERE name = :name;";

QString WorkerClientDataBase::get_new_name_connection()
{
    int id = 0;
    auto temp = QThread::currentThreadId();
    memcpy(&id,&temp,sizeof (id));
    return DEFAULT_NAME_CONNECTION_DATA_BASE + QString::number(id);
}

void WorkerClientDataBase::remove_connection(const QString &name_connection)
{
    QSqlDatabase::removeDatabase(name_connection);
}

QStringList WorkerClientDataBase::get_all_user()const
{
    QMutexLocker lock(&_data_base_mutex);

    QStringList res;
    QSqlQuery query(_base);
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
    QMutexLocker lock(&_data_base_mutex);

    QSqlQuery query(_base);
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
    QMutexLocker lock(&_data_base_mutex);

    QSqlQuery query(_base);
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
    QMutexLocker lock(&_data_base_mutex);

    QSqlQuery query(_base);
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
    QMutexLocker lock(&_data_base_mutex);

    if(_base.isOpen() && is_user(user))
    {
        _base.transaction();
        QSqlQuery query(_base);
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
    QMutexLocker lock(&_data_base_mutex);

    if(_base.isOpen())
    {
        _base.transaction();
        QSqlQuery query(_base);
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
    QMutexLocker lock(&_data_base_mutex);

    QStringList res;
    QSqlQuery query(_base);
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
    QMutexLocker lock(&_data_base_mutex);

    if(_base.isOpen() && is_user(user))
    {
        _base.transaction();
        QSqlQuery query(_base);
        query.prepare(INSERT_FILES_REQUEST);
        for(auto it = data.begin(); it != data.end(); it++)
        {
            query.bindValue(":name",user);
            query.bindValue(":path",it.key());
            query.bindValue(":created_data",std::get<INDEX_CREATED>(it.value()));
            query.bindValue(":last_modified_data",std::get<INDEX_LAST_MODIFIED>(it.value()));
            query.bindValue(":size",QString::number(std::get<INDEX_SIZE>(it.value())));

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
    QMutexLocker lock(&_data_base_mutex);

    if(_base.isOpen())
    {
        _base.transaction();
        QSqlQuery query(_base);
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
    QMutexLocker lock(&_data_base_mutex);

    FileMetaData res;
    QSqlQuery query(_base);
    query.prepare(SELECT_FILES_REQUEST);
    query.bindValue(":name",user);
    if(_base.isOpen() && query.exec())
    {
        while(query.next())
        {
            auto path = query.value("path").toString();
            quint64 size = static_cast<quint64>(query.value("size").toString().toDouble());
            auto created_data = query.value("created_data").toString();
            auto last_modified_data = query.value("last_modified_data").toString();
            FileCharacteristics data = std::make_tuple(size,created_data,last_modified_data);
            res.insert(path,data);
        }
    }
    return res;
}

bool WorkerClientDataBase::insert_task_user(const QString &user, const QStringList &files, const QStringList &local_files, const QStringList &dates)
{
    QMutexLocker lock(&_data_base_mutex);

    if(_base.isOpen() && is_user(user))
    {
        _base.transaction();
        QSqlQuery query(_base);
        query.prepare(INSERT_TASK_REQUEST);
        for(int index = 0; index < files.size(); index++)
        {
            query.bindValue(":name",user);
            query.bindValue(":file",files[index]);
            query.bindValue(":local_file",local_files[index]);
            query.bindValue(":last_modified",dates[index]);
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

bool WorkerClientDataBase::update_task_user(const QString &user,const QString &file, const QString &date)
{
    QMutexLocker lock(&_data_base_mutex);

    if(_base.isOpen() && is_user(user))
    {
        _base.transaction();
        QSqlQuery query(_base);
        query.prepare(UPDATE_LAST_MODIFIED_TASK_FILE_REQUEST);
        query.bindValue(":name",user);
        query.bindValue(":file",file);
        query.bindValue(":last_modified",date);
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

bool WorkerClientDataBase::delete_task_user(const QString &user, const QStringList &files)
{
    QMutexLocker lock(&_data_base_mutex);

    if(_base.isOpen() && is_user(user))
    {
        _base.transaction();
        QSqlQuery query(_base);
        query.prepare(DELETE_TASK_USER_REQUEST);
        for(int index = 0; index < files.size(); index++)
        {
            query.bindValue(":name",user);
            query.bindValue(":file",files[index]);
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

bool WorkerClientDataBase::delete_all_task_user(const QString &user)
{
    QMutexLocker lock(&_data_base_mutex);

    if(_base.isOpen())
    {
        _base.transaction();
        QSqlQuery query(_base);
        query.prepare(DELETE_ALL_TASK_USER_REQUEST);
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

WorkerClientDataBase::Tasks WorkerClientDataBase::get_all_task_user(const QString &user)const
{
    QMutexLocker lock(&_data_base_mutex);

    QStringList files;
    QStringList local_files;
    QStringList dates;
    QSqlQuery query(_base);
    query.prepare(SELECT_ANY_TASK_REQUEST);
    query.bindValue(":name",user);
    if(_base.isOpen() && query.exec())
    {
        while(query.next())
        {
            files += query.value("file").toString();
            local_files += query.value("local_file").toString();
            dates += query.value("last_modified").toString();
        }
    }
    return qMakePair(qMakePair(files,local_files),dates);
}

QMap<QString,WorkerClientDataBase::Tasks> WorkerClientDataBase::get_all_task_users()const
{
    QMutexLocker lock(&_data_base_mutex);

    QMap<QString,Tasks> res;
    QSqlQuery query(_base);
    query.prepare(SELECT_TASK_REQUEST);
    if(_base.isOpen() && query.exec())
    {
        while(query.next())
        {
            auto user = query.value("name").toString();
            res[user] = get_all_task_user(user);
        }
    }
    return res;
}

bool WorkerClientDataBase::is_user_info(const QString &user)
{
    QMutexLocker lock(&_data_base_mutex);

    return get_addr_info_user(user).first == "null" ? false : true;
}

bool WorkerClientDataBase::insert_addr_info_user(const QString &user,const QString &addr, quint16 port)
{
    QMutexLocker lock(&_data_base_mutex);

    if(_base.isOpen() && is_user(user))
    {
        _base.transaction();
        QSqlQuery query(_base);
        query.prepare(INSERT_ADDR_INFO_USER_REQUEST);
        query.bindValue(":name",user);
        query.bindValue(":port",port);
        query.bindValue(":addr",addr);
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

bool WorkerClientDataBase::change_addr_user(const QString &user,const QString &addr)
{
    QMutexLocker lock(&_data_base_mutex);

    if(_base.isOpen() && is_user(user))
    {
        _base.transaction();
        QSqlQuery query(_base);
        query.prepare(UPDATE_ADDR_USER_REQUEST);
        query.bindValue(":name",user);
        query.bindValue(":addr",addr);
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

bool WorkerClientDataBase::change_port_user(const QString &user,quint16 port)
{
    QMutexLocker lock(&_data_base_mutex);

    if(_base.isOpen() && is_user(user))
    {
        _base.transaction();
        QSqlQuery query(_base);
        query.prepare(UPDATE_PORT_USER_REQUEST);
        query.bindValue(":name",user);
        query.bindValue(":port",port);
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

bool WorkerClientDataBase::delete_addr_info_user(const QString &user)
{
    QMutexLocker lock(&_data_base_mutex);

    if(_base.isOpen())
    {
        _base.transaction();
        QSqlQuery query(_base);
        query.prepare(DELETE_ADDR_INFO_REQUEST);
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

QPair<QString,quint16> WorkerClientDataBase::get_addr_info_user(const QString &user)
{
    QMutexLocker lock(&_data_base_mutex);

    QPair<QString,quint16> res("null",0);
    QSqlQuery query(_base);
    query.prepare(SELECT_ANY_ADDR_INFO_REQUEST);
    query.bindValue(":name",user);
    if(_base.isOpen() && query.exec())
    {
        if(query.next())
        {
            res.first = query.value("addr").toString();
            res.second = static_cast<quint16>(query.value("port").toInt());
        }
    }
    return res;
}

WorkerClientDataBase::WorkerClientDataBase(const QString &connection_name)
{
    if(QSqlDatabase::contains(connection_name))
    {
        QSqlDatabase::database(connection_name);
    }
    else
    {
        _base = QSqlDatabase::addDatabase(TYPE_DATA_BASE,connection_name);
        _base.setDatabaseName(DEFAULT_NAME_DATA_BASE);
        _base.open();
    }
}

WorkerClientDataBase::~WorkerClientDataBase()
{
    _base.close();
}
