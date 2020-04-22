#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    _proxy.start();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_work_button_clicked()
{
    if(_serv.isNull())
    {
        _serv.reset(new BaseServer(ui->serv_addr->text(),ui->serv_port->text().toInt()));

        connect(_serv.get(),&BaseServer::new_connection,this,[&]
        {
            _serv->add_connection();
            auto temp = _serv->info_connection();
            if(temp.size())
            {
                ui->terminal->addItem("new connection " + temp[temp.size() - 1].first + ":" + QString::number(temp[temp.size() - 1].second));
            }

        });

        connect(_serv.get(),&BaseServer::socket_error,this,[&](QTcpSocket *socket, QAbstractSocket::SocketError state)
        {
            ui->terminal->addItem("Error " + QString::number(state));
        });

        connect(_serv.get(),&BaseServer::disconnected_socket,this,[&](QTcpSocket *socket)
        {
            ui->terminal->addItem("disconnected ");
            _worker_data_client.remove_client(socket);
        });
        connect(_serv.get(),&BaseServer::ready_data_read,this,&MainWindow::slot_ready_read);
    }
    if(_serv->is_run())
    {
        _serv->stop();
    }
    else
    {
        _serv->run();
    }
}

void MainWindow::slot_ready_read(QTcpSocket *socket)
{

    QByteArray data;
    _serv->read_data(socket,data);

    auto task = new TaskRecvMsg(&info_recv_data[socket],data);
    connect(task,&TaskRecvMsg::recved_data,_serv.get(),[socket,this]()
    {
        _worker_data_client.change_data(socket,info_recv_data[socket]._msg);
        info_recv_data[socket].clear();
        slot_send_data({socket});
    }, Qt::ConnectionType::DirectConnection);
    _proxy.push(task);

}

void MainWindow::slot_send_data(const QList<QTcpSocket *> &source)
{
    auto users = _serv->get_client_sockets();
    for(auto s : source)
    {
        users.removeOne(s);
    }

    QByteArray temp;
    _worker_data_client.create_sended_data(temp,source);
    if(users.size())
    {
        for(auto user: users)
        {
            auto task = new TaskSendMsg(temp,&_proxy);
            connect(task,&TaskSendMsg::send_data,user,[&,user](QByteArray array)
            {
               _serv->write_data(user,array);
            }, Qt::ConnectionType::QueuedConnection);
            _proxy.push(task);
        }
    }
}
