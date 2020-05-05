#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Tasks/taskrecvmsg.h"
#include "Tasks/tasksendmsg.h"
#include "BaseServer/base_server.h"
#include "Workers/workerdataclient.h"

#include <QMainWindow>
#include <QSharedPointer>
#include <QMap>
#include <QMutex>
#include <QMutexLocker>

namespace Ui {
class MainWindow;
}

class WindowServer : public QMainWindow
{
    Q_OBJECT

    using FileCharacteristics = std::tuple<quint64,QString,QString>;
    using FileMetaData = QMap<QString,FileCharacteristics>;
    using DirsPath = QStringList;
    using MetaDataDir = QPair<DirsPath,FileMetaData>;
    using UserInfo = QPair<QString,quint16>;

public:
    explicit WindowServer(QWidget *parent = nullptr);
    ~WindowServer();

private slots:
    void on_work_button_clicked();
    void slot_ready_read(QTcpSocket *socket);
    void slot_send_data(const QList<QTcpSocket *> &source);

private:
    Ui::MainWindow *ui;
    WorkDataClientOnServer::WorkerDataClient _worker_data_client;

    QSharedPointer<DataTransfer::BaseServer> _serv;
    ActiveObject::ProxyActiveObject _proxy;

    QMap<QTcpSocket*, TasksServer::TaskRecvMsg::WorkInfo> _info_recv_data;

    QMap<QTcpSocket*, UserInfo> _users;

    void send_msg(QTcpSocket *socket, const QByteArray &data);
};

#endif // MAINWINDOW_H
