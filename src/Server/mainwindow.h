#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include <QMap>

#include <Tasks/taskrecvmsg.h>
#include <Tasks/tasksendmsg.h>

#include <BaseServer/base_server.h>

#include <workerdataclient.h>

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
    void slot_send_data(const QList<QTcpSocket *> &source);

private:
    Ui::MainWindow *ui;
    WorkerDataClient _worker_data_client;

    QSharedPointer<DataTransfer::BaseServer> _serv;
    ActiveObject::ProxyActiveObject _proxy;

    QMap<QTcpSocket*,TaskRecvMsg::WorkInfo> info_recv_data;

    void send_msg(QTcpSocket *socket, const QByteArray &data);


};

#endif // MAINWINDOW_H
