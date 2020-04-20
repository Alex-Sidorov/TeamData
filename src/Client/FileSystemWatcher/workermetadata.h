#ifndef WORKERMETADATA_H
#define WORKERMETADATA_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QStringList>
#include <QMap>
#include <QByteArray>
#include <tuple>
#include <QFileSystemWatcher>
#include <QDateTime>
#include <QMap>
#include <QMutex>

#include "BaseClient/base_client.h"
#include "ActiveObject/proxyactiveobject.h"
#include "taskrecvmsg.h"

class WorkerMetaData : public QObject
{
    Q_OBJECT

    using CLIENT = DataTransfer::BaseClient;
    using PROXY =  ActiveObject::ProxyActiveObject;
public:
    using FileCharacteristics = std::tuple<quint64,QString,QString>;
    using FileMetaData = QMap<QString,FileCharacteristics>;
    using DirsPath = QStringList;
    using MetaDataDir = QPair<DirsPath,FileMetaData>;
    using UserInfo = QPair<QString,QString>;

    WorkerMetaData(PROXY *proxy, CLIENT *client = nullptr);
    WorkerMetaData(PROXY *proxy, QString &path, CLIENT *client = nullptr);
    WorkerMetaData(PROXY *proxy, QString &&path, CLIENT *client = nullptr);
    virtual ~WorkerMetaData();

    void change_dir(QString &path);
    void change_dir(QString &&path);

    void change_client(CLIENT *client);

    void scan_dir();
    void create_sended_data(QByteArray &data);
    void parse_recved_data(QByteArray &data);

signals:
    void upload_tree(MetaDataDir data);
    void new_files(FileMetaData data);
    void removed_files(FileMetaData data);
    void new_dirs(QStringList data);
    void removed_dirs(QStringList data);

public slots:
    void files_changed(const QString &path);
    void dir_changed(const QString &path);

    static void remove_root_path(QString &path, QStringList &data);

private:
    QString _path;
    PROXY *_proxy;
    CLIENT *_client;

    QMap<UserInfo,MetaDataDir> _remote_meta_data;

    MetaDataDir _meta_data;
    MetaDataDir _present_meta_data;

    QFileSystemWatcher _watcher;
    TaskRecvMsg::WorkInfo info_recv_data;

    QMutex _mutex;

    void add_dirs_path(QStringList &dirs);

    /*void init_dir_tree(QStringList &files, QStringList &dirs);
    void insert_dir(QString &dir);
    void insert_file(DirTree &tree, QString &file);*/
};

#endif // WORKERMETADATA_H
