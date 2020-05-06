#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

WindowServer::WindowServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    _proxy.start();
    ui->setupUi(this);
}

WindowServer::~WindowServer()
{
    delete ui;
}

void WindowServer::on_work_button_clicked()
{
    if(_serv.isNull())
    {
        _serv.reset(new DataTransfer::BaseServer(ui->serv_addr->text(),static_cast<quint16>(ui->serv_port->text().toInt())));

        connect(_serv.get(),&DataTransfer::BaseServer::new_connection,this,[this]
        {
            _serv->add_connection();

            auto info = _serv->info_connection().back();
            ui->terminal->addItem("Подключился:" + info.first + QString::number(info.second));

            auto client = _serv->get_client_sockets().back();
            _users[client] = info;

            QByteArray temp;
            _worker_data_client.get_full_meta_data(temp);
            send_msg(client,temp);
        });

        connect(_serv.get(),&DataTransfer::BaseServer::disconnected_socket,this,[&](QTcpSocket *socket)
        {
            auto &info = _users[socket];
            ui->terminal->addItem("Отключился:" + info.first + QString::number(info.second));
            _users.remove(socket);

            _serv->remove_connection(socket);
            _worker_data_client.remove_client(socket);
        });
        connect(_serv.get(),&DataTransfer::BaseServer::ready_data_read,this,&WindowServer::slot_ready_read);
    }
    if(_serv->is_run())
    {
        _serv->stop();
        ui->work_button->setText("Запустить сервер");
        ui->serv_addr->setEnabled(true);
        ui->serv_port->setEnabled(true);
        ui->statusBar->clearMessage();
    }
    else
    {
        if(_serv->run())
        {
            ui->work_button->setText("Остановить сервер");
            ui->serv_addr->setEnabled(false);
            ui->serv_port->setEnabled(false);
            ui->statusBar->showMessage("Сервер работает");
        }
        else
        {
            QMessageBox::warning(nullptr,"Ошибка","Не удалось запустить сервер");
        }
    }
}

void WindowServer::slot_ready_read(QTcpSocket *socket)
{

    QByteArray data;
    _serv->read_data(socket,data);

    auto task = new TasksServer::TaskRecvMsg(&_info_recv_data[socket],data);
    connect(task,&TasksServer::TaskRecvMsg::recved_data,_serv.get(),[socket,this]()
    {
        _worker_data_client.change_data(socket, _info_recv_data[socket]._msg);
        _info_recv_data[socket].clear();
        slot_send_data({socket});
    }, Qt::ConnectionType::DirectConnection);
    _proxy.push(task);

}

void WindowServer::slot_send_data(const QList<QTcpSocket *> &source)
{
    auto users = _serv->get_client_sockets();
    for(auto s : source)
    {
        users.removeOne(s);
    }

    QByteArray temp;
    _worker_data_client.fill_transfers_data(temp,source);
    if(users.size())
    {
        for(auto user: users)
        {
            send_msg(user, temp);
        }
    }
}

void WindowServer::send_msg(QTcpSocket *socket, const QByteArray &data)
{
    auto task = new TasksServer::TaskSendMsg(data,&_proxy);
    connect(task,&TasksServer::TaskSendMsg::send_data,socket,[&,socket](QByteArray array)
    {
       _serv->write_data(socket,array);
    }, Qt::ConnectionType::QueuedConnection);
    _proxy.push(task);
}
