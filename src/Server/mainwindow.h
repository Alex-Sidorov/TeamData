#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>

#include <Tasks/taskrecvmsg.h>
#include <Tasks/tasksendmsg.h>

#include <BaseServer/base_server.h>

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
    void on_work_button_clicked();
    void slot_ready_read(QTcpSocket *socket);

    void on_send_button_clicked();

private:
    Ui::MainWindow *ui;

    QSharedPointer<DataTransfer::BaseServer> _serv;
    ActiveObject::ProxyActiveObject _proxy;

    QSharedPointer<TaskRecvMsg>task_recv_msg;
};

#endif // MAINWINDOW_H
