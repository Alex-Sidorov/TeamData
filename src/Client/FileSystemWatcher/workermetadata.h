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

#include "settings.h"

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
    using UserInfo = QPair<QString,quint16>;

    WorkerMetaData(PROXY *proxy, CLIENT *client = nullptr);
    virtual ~WorkerMetaData();

    void change_dir(QString &path);
    void change_dir(QString &&path);

    void change_client(CLIENT *client);

    void scan_dir();
    void create_sended_data(QByteArray &data);
    void parse_recved_data(QByteArray &data);

    static void remove_root_path(QString &path, QStringList &data);

    void load_data_from_database();

signals:
    void upload_tree(MetaDataDir data, QString name);
    void new_files(FileMetaData data);
    void removed_files(FileMetaData data);
    void new_dirs(QStringList data);
    void removed_dirs(QStringList data);

public slots:
    void files_changed(const QString &path);
    void dir_changed(const QString &path);

private:
    QString _name;
    QString _path;
    PROXY *_proxy;
    CLIENT *_client;

    Settings _settings;

    QMap<QString,UserInfo> _users;
    QMap<QString,MetaDataDir> _remote_meta_data;

    MetaDataDir _meta_data;
    MetaDataDir _present_meta_data;

    QFileSystemWatcher _watcher;
    TaskRecvMsg::WorkInfo _info_recv_data;

    QMutex _mutex;

    void add_dirs_path(QStringList &dirs);
    void remove_watcher_path();
};

#endif // WORKERMETADATA_H
