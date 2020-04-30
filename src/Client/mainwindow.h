#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include <QTreeWidget>
#include <QMap>
#include <QPair>

#include <tasksendmsg.h>
#include <taskrecvmsg.h>

#include <settings.h>
#include <BaseClient/base_client.h>
#include <ActiveObject/proxyactiveobject.h>
#include <FileSystemWatcher/workermetadata.h>
#include <workerremoteclient.h>

using DataTransfer::BaseClient;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_select_path_button_clicked();
    void slot_removed_dirs(QStringList dirs);
    void slot_load_tree(WorkerMetaData::MetaDataDir data, QString name);

    void on_users_doubleClicked(const QModelIndex &index);

    void on_name_line_editingFinished();

    void on_self_addr_editingFinished();

    void on_serv_addr_editingFinished();

    void on_serv_port_valueChanged(int arg1);

    void on_self_port_valueChanged(int arg1);

    void on_path_line_editingFinished();

    void on_work_serv_clicked();


    void on_tree_dir_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;

    QMap<QString,QPair<size_t,QTreeWidget*>> _remote_dir;

    QSharedPointer<BaseClient>_client;
    ActiveObject::ProxyActiveObject _proxy;
    TaskRecvMsg::WorkInfo info_recv_data;
    WorkerMetaData worker_meta_data;
    WorkerRemoteClient _worker_remote_client;

    Settings _settings;

    void remove_items_tree(WorkerMetaData::MetaDataDir data);

    void add_dirs(QTreeWidget *tree, QStringList &dirs);
    void add_files(QTreeWidget *tree, WorkerMetaData::FileMetaData &files);


};

#endif // MAINWINDOW_H
