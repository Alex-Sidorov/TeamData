#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include <QMap>

#include <Tasks/taskrecvmsg.h>
#include <Tasks/tasksendmsg.h>

#include <BaseServer/base_server.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    using FileCharacteristics = std::tuple<quint64,QString,QString>;
    using FileMetaData = QMap<QString,FileCharacteristics>;
    using DirsPath = QStringList;
    using MetaDataDir = QPair<DirsPath,FileMetaData>;
    using UserInfo = QPair<QString,QString>;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_work_button_clicked();
    void slot_ready_read(QTcpSocket *socket);

    void on_send_button_clicked();

private:
    Ui::MainWindow *ui;

    QSharedPointer<DataTransfer::BaseServer> _serv;
    ActiveObject::ProxyActiveObject _proxy;

    QMap<QTcpSocket*,TaskRecvMsg::WorkInfo> info_recv_data;

    QSharedPointer<TaskRecvMsg>task_recv_msg;

    void create_sended_data(QByteArray &data, const QList<QTcpSocket *> &source);
    void parse_recved_data(QTcpSocket *client, QByteArray &data);
    void add_files(FileMetaData &files);
    void add_dirs(QStringList &dirs);

    void send_data(const QList<QTcpSocket *> &source);


    QMap<QTcpSocket*,MetaDataDir> _remote_meta_data;
};

#endif // MAINWINDOW_H
