#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include <QDirModel>

#include <tasksendmsg.h>
#include <taskrecvmsg.h>

#include <BaseClient/base_client.h>
#include <ActiveObject/proxyactiveobject.h>
#include <FileSystemWatcher/workermetadata.h>

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
    void on_send_button_clicked();
    void slot_ready_read();
    void on_select_path_button_clicked();
    void on_scan_dir_button_clicked();
    void slot_exec_file(const QModelIndex &index);

    void slot_removed_dirs(QStringList dirs);
    void slot_load_tree(WorkerMetaData::MetaDataDir data);

private:
    Ui::MainWindow *ui;

    QSharedPointer<BaseClient>_client;
    ActiveObject::ProxyActiveObject _proxy;
    TaskRecvMsg::WorkInfo info_recv_data;
    WorkerMetaData worker_meta_data;
    QDirModel _model;

    void remove_items_tree(WorkerMetaData::MetaDataDir data);

    void add_dirs(QStringList &dirs);
    void add_files(WorkerMetaData::FileMetaData &files);
};

#endif // MAINWINDOW_H
