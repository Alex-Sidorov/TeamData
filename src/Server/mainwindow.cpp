#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
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
            ui->terminal->addItem("Error " /*+ socket->localAddress().toString() + " "  */+ QString::number(state));
        });

        connect(_serv.get(),&BaseServer::disconnected_socket,this,[&](QTcpSocket *socket)
        {
            ui->terminal->addItem("disconnected " /*+ socket->localAddress().toString()*/);
        });

        connect(_serv.get(),&BaseServer::recved_data,this,[&]
        {
            ui->terminal->addItem(task_recv_msg->get_msg());
            task_recv_msg.reset();
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
    /*if(task_recv_msg.isNull())
    {
        task_recv_msg.reset(new TaskRecvMsg(_serv.get(),socket,&_proxy));
        _proxy.push(task_recv_msg.get());
    }*/
    QByteArray data;
    _serv->read_data(socket,data);
    ui->terminal->addItem(data);
}

void MainWindow::on_send_button_clicked()
{
    qDebug()<<"send";
    QByteArray data = ui->input_line->text().toLatin1();
    data.push_front(BaseServer::IntToArray(data.size()));
    _serv->write_data(0,data);
}
