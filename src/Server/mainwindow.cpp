#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    _proxy.start();
    ui->setupUi(this);
    qDebug() << "MT" << QThread::currentThreadId();
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

        /*connect(_serv.get(),&BaseServer::recved_data,this,[&]
        {
            ui->terminal->addItem(task_recv_msg->get_msg());
            task_recv_msg.reset();
        });*/
        connect(_serv.get(),&BaseServer::ready_data_read,this,&MainWindow::slot_ready_read);
    }
    if(_serv->is_run())
    {
        _serv->stop();
        _remote_meta_data.clear();
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
        parse_recved_data(socket,info_recv_data[socket]._msg);
        info_recv_data[socket].clear();
        send_data({socket});
        qDebug() << "MT" << QThread::currentThreadId();
    }, Qt::ConnectionType::DirectConnection);
    _proxy.push(task);

}

void MainWindow::on_send_button_clicked()
{
    qDebug()<<"send";
    QByteArray data = ui->input_line->text().toLatin1();
    data.push_front(BaseServer::IntToArray(data.size()));
    _serv->write_data(0,data);
}

void MainWindow::parse_recved_data(QTcpSocket *client, QByteArray &data)
{
    QDataStream stream(&data,QIODevice::ReadOnly);

    QString name;
    QString addr;
    MetaDataDir meta_data;

    stream >> meta_data.first ;
    while(!stream.atEnd())
    {
        QString name_file;
        FileCharacteristics file_info;
        stream >> name_file >> std::get<0>(file_info)
                            >> std::get<1>(file_info)
                            >> std::get<2>(file_info);
        meta_data.second.insert(name_file,file_info);
    }
    _remote_meta_data[client] = meta_data;
    //add_dirs(meta_data.first);
    //add_files(meta_data.second);
}

void MainWindow::create_sended_data(QByteArray &data,const  QList<QTcpSocket *> &source)
{
    QDataStream stream(&data,QIODevice::WriteOnly);

    stream << static_cast<size_t>(source.size());
    for(auto user : source)
    {
        int count_files = _remote_meta_data[user].second.size();
        stream << user->peerAddress().toString()
               << QString("user")
               << _remote_meta_data[user].first
               << count_files;

        auto &map = _remote_meta_data[user].second;
        for(auto it = map.begin(); it != map.end(); it++)
        {
            stream << it.key() << std::get<0>(it.value())
                               << std::get<1>(it.value())
                               << std::get<2>(it.value());
        }
    }
}

void MainWindow::send_data(const QList<QTcpSocket *> &source)
{
    auto users = _serv->get_client_sockets();
    for(auto s : source)
    {
        users.removeOne(s);
    }
    if(users.size())
    {
        QByteArray temp;
        create_sended_data(temp,source);

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

void MainWindow::add_dirs(QStringList &dirs)
{
    for(auto it = dirs.begin(); it != dirs.end(); it++)
    {
        auto path = it->split('/');
        ui->tree_dir->setCurrentItem(nullptr);
        for(int i = 0; i < path.size(); i++)
        {
            if(!path[i].isEmpty())
            {
                auto cur = ui->tree_dir->currentItem();
                if(!cur)
                {
                    auto v = ui->tree_dir->findItems(path[i],Qt::MatchFlag::MatchFixedString);
                    if(v.size())
                    {
                        ui->tree_dir->setCurrentItem(v[0]);
                    }
                    else
                    {
                        auto name = new QTreeWidgetItem(QStringList(path[i]));
                        name->setIcon(0,QApplication::style()->standardIcon(QStyle::SP_DirIcon));
                        auto ptr = ui->tree_dir->currentItem();
                        if(ptr)
                        {
                            ptr->addChild(name);
                        }
                        else
                        {
                            ui->tree_dir->insertTopLevelItem(0,name);
                        }
                        ui->tree_dir->setCurrentItem(name);
                    }
                }
                else
                {
                    bool is_be = false;
                    for(int j = 0; j < cur->childCount(); j++)
                    {
                        if(cur->child(j)->text(0) == path[i])
                        {
                            is_be = true;
                            ui->tree_dir->setCurrentItem(cur->child(j));
                            break;
                        }
                    }
                    if(!is_be)
                    {
                        auto name = new QTreeWidgetItem(QStringList(path[i]));
                        name->setIcon(0,QApplication::style()->standardIcon(QStyle::SP_DirIcon));
                        auto ptr = ui->tree_dir->currentItem();
                        if(ptr)
                        {
                            ptr->addChild(name);
                        }
                        else
                        {
                            ui->tree_dir->insertTopLevelItem(0,name);
                        }
                        ui->tree_dir->setCurrentItem(name);
                    }
                }
            }
        }
    }
    ui->tree_dir->setCurrentItem(nullptr);
}

void MainWindow::add_files(FileMetaData &files)
{
    for(auto it = files.begin(); it != files.end(); it++)
    {
        auto path = it.key().split('/');
        auto data = it.value();
        ui->tree_dir->setCurrentItem(nullptr);
        for(int i = 0; i < path.size(); i++)
        {
            if(path[i].isEmpty())
            {
                continue;
            }
            else if(i + 1 == path.size())
            {
                auto name = new QTreeWidgetItem(QStringList(path[i]));
                name->setText(1,QString::number(std::get<0>(data)) + " Байт");
                name->setText(2,std::get<1>(data));
                name->setText(3,std::get<2>(data));
                name->setIcon(0,QApplication::style()->standardIcon(QStyle::SP_FileIcon));
                auto ptr = ui->tree_dir->currentItem();
                if(ptr)
                {
                    ptr->addChild(name);
                }
                else
                {
                    ui->tree_dir->insertTopLevelItem(0,name);
                }
            }
            else
            {
                auto cur = ui->tree_dir->currentItem();
                if(!cur)
                {
                    ui->tree_dir->setCurrentItem(ui->tree_dir->findItems(path[i],Qt::MatchFlag::MatchFixedString)[0]);
                }
                else
                {
                    for(int j = 0; j < cur->childCount(); j++)
                    {
                        if(cur->child(j)->text(0) == path[i])
                        {
                            ui->tree_dir->setCurrentItem(cur->child(j));
                            break;
                        }
                    }
                }
            }
        }
    }
    ui->tree_dir->setCurrentItem(nullptr);
}
