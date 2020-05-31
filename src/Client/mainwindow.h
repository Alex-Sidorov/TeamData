#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Tasks/tasksendmsg.h"
#include "Tasks/taskrecvmsg.h"
#include "Settings/settings.h"
#include "BaseClient/base_client.h"
#include "ActiveObject/proxyactiveobject.h"
#include "Workers/workermetadata.h"
#include "Workers/workerremoteclient.h"

#include <QMainWindow>
#include <QSharedPointer>
#include <QTreeWidget>
#include <QMap>
#include <QPair>
#include <QColor>

using DataTransfer::BaseClient;

namespace Ui {
class MainWindow;
}

class WindowClient : public QMainWindow
{
    Q_OBJECT


public:
    explicit WindowClient(QWidget *parent = nullptr);
    ~WindowClient();

private slots:
    void on_pushButton_clicked();
    void on_select_path_button_clicked();
    void on_users_doubleClicked(const QModelIndex &index);
    void on_name_line_editingFinished();
    void on_self_addr_editingFinished();
    void on_serv_addr_editingFinished();
    void on_serv_port_valueChanged(int arg1);
    void on_self_port_valueChanged(int arg1);
    void on_path_line_editingFinished();
    void on_work_serv_clicked();
    void on_search_button_clicked();
    void on_search_line_returnPressed();

    void slot_download_file(QTreeWidgetItem *item);
    bool slot_insert_task(QTreeWidgetItem *item);
    bool slot_delete_task(QTreeWidgetItem *item);
    void slot_removed_dirs(QStringList dirs);
    void slot_load_tree(WorkMetaDataOnClient::WorkerMetaData::MetaDataDir data, QString name);
    void slot_sub_menu(const QPoint &pos);

private:
    Ui::MainWindow *ui;

    QMap<QString,QPair<size_t,QTreeWidget*>> _remote_dir;

    QSharedPointer<BaseClient>_client;
    ActiveObject::ProxyActiveObject _proxy;
    WorkMetaDataOnClient::WorkerMetaData _worker_meta_data;
    WorkRemoteDevice::WorkerRemoteClient _worker_remote_client;

    SettingsClient::Settings _settings;
    QList<QTreeWidgetItem*> _search_res;

    void add_dirs(QTreeWidget *tree, QStringList &dirs);
    void add_files(const QString &name, QTreeWidget *tree, WorkMetaDataOnClient::WorkerMetaData::FileMetaData &files);
    QString get_absolute_path(QTreeWidgetItem *item);

    QList<QTreeWidgetItem*> search_item(QTreeWidget *tree, const QString &text);

    static const QColor TASK_COLOR;
    static const QColor DEFAULT_COLOR;
};

#endif // MAINWINDOW_H
