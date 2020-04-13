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
#include <FileSystemWatcher/dirtree.h>

class WorkerMetaData : public QObject
{
    Q_OBJECT
public:
    using FileCharacteristics = std::tuple<quint64,QString,QString>;
    using FileMetaData = QMap<QString,FileCharacteristics>;
    using DirsPath = QStringList;
    using MetaDataDir = QPair<DirsPath,FileMetaData>;

    WorkerMetaData();
    WorkerMetaData(QString &path);
    WorkerMetaData(QString &&path);
    virtual ~WorkerMetaData();

    void change_dir(QString &path);
    void change_dir(QString &&path);

    void scan_dir();
    void create_sended_data(QByteArray &data);

signals:
    void upload_tree(MetaDataDir data);
    void new_files(FileMetaData data);
    void removed_files(FileMetaData data);

public slots:
    void files_changed(const QString &path);
    void dir_changed(const QString &path);

private:
    QString _path;
    MetaDataDir _meta_data;
    MetaDataDir _present_meta_data;
    QFileSystemWatcher _watcher;

    DirTree _tree;

    void remove_root_path(QString &path, QStringList &data) const;

    QStringList get_added_files(const QStringList &scan_files)const;
    QStringList get_removed_files(const QStringList &scan_files, const QString &path)const;
    QStringList get_added_folders(const QStringList &scan_files)const;
    QStringList get_removed_folders(const QStringList &scan_files, const QString &path)const;
    /*void init_dir_tree(QStringList &files, QStringList &dirs);
    void insert_dir(QString &dir);
    void insert_file(DirTree &tree, QString &file);*/
};

#endif // WORKERMETADATA_H
