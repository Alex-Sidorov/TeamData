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
#include <QList>
#include <QMutex>

#include <FileSystemWatcher/dirtree.h>
#include "ActiveObject/proxyactiveobject.h"

class WorkerMetaData : public QObject
{
    Q_OBJECT

    using PROXY =  ActiveObject::ProxyActiveObject;
public:
    using FileCharacteristics = std::tuple<quint64,QString,QString>;
    using FileMetaData = QMap<QString,FileCharacteristics>;
    using DirsPath = QStringList;
    using MetaDataDir = QPair<DirsPath,FileMetaData>;

    WorkerMetaData(PROXY *proxy);
    WorkerMetaData(PROXY *proxy, QString &path);
    WorkerMetaData(PROXY *proxy, QString &&path);
    virtual ~WorkerMetaData();

    void change_dir(QString &path);
    void change_dir(QString &&path);

    void scan_dir();
    void create_sended_data(QByteArray &data);

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

    MetaDataDir _meta_data;
    MetaDataDir _present_meta_data;
    QFileSystemWatcher _watcher;
    QMutex _mutex;

    DirTree _tree;

    void add_dirs_path(QStringList &dirs);

    QStringList get_added_files(const QStringList &scan_files)const;
    QStringList get_removed_files(const QStringList &scan_files, const QString &path)const;
    QStringList get_added_folders(const QStringList &scan_files)const;
    QStringList get_removed_folders(const QStringList &scan_files, const QString &path)const;
    /*void init_dir_tree(QStringList &files, QStringList &dirs);
    void insert_dir(QString &dir);
    void insert_file(DirTree &tree, QString &file);*/
};

#endif // WORKERMETADATA_H
