#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTreeWidget>
#include <QTreeWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    info_recv_data({"",0,false}),
    worker_meta_data(&_proxy)
{
    _proxy.start();
    ui->setupUi(this);
    ui->terminal->setVisible(false);

    connect(&worker_meta_data,&WorkerMetaData::upload_tree,this,&MainWindow::slot_load_tree);
    //connect(&worker_meta_data,&WorkerMetaData::removed_dirs,this,&MainWindow::slot_removed_dirs);
    connect(ui->tree_dir,&QTreeWidget::doubleClicked,this,&MainWindow::slot_exec_file);

    worker_meta_data.change_dir("D:\\dir");
    worker_meta_data.scan_dir();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_load_tree(WorkerMetaData::MetaDataDir data)
{
    ui->tree_dir->clear();
    add_dirs(data.first);
    add_files(data.second);
}

void MainWindow::add_dirs(QStringList &dirs)
{
    for(int i = 0; i < dirs.size(); i++)
    {
        auto path = dirs[i].split('/');
        ui->tree_dir->setCurrentItem(nullptr);
        for(auto &p: path)
        {
            if(p.isEmpty())
            {
                continue;
            }
            auto item = ui->tree_dir->findItems(p,Qt::MatchFlag::MatchFixedString);
            if(!item.empty())
            {
                ui->tree_dir->setCurrentItem(item[0]);
                continue;
            }
            else
            {
                auto value = new QTreeWidgetItem(QStringList(p));
                value->setIcon(0,QApplication::style()->standardIcon(QStyle::SP_DirIcon));
                if(ui->tree_dir->currentItem())
                {
                    ui->tree_dir->currentItem()->addChild(value);
                    ui->tree_dir->setCurrentItem(value);
                }
                else
                {
                    ui->tree_dir->insertTopLevelItem(0,value);
                    ui->tree_dir->setCurrentItem(value);
                }
            }
        }
    }
}

void MainWindow::add_files(WorkerMetaData::FileMetaData &files)
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
}

//todo
void MainWindow::slot_removed_dirs(QStringList dirs)
{
    for(int i = 0; i < dirs.size(); i++)
    {
        auto path = dirs[i].split('/');
        path.removeAll("");
        auto values = ui->tree_dir->findItems(path.back(),Qt::MatchFlag::MatchRecursive);
        for(auto item : values)
        {
            QString temp;
            auto value = item;
            do
            {
                temp.push_front('/' + value->text(0));
                value = value->parent();
            }while(value);
            if(temp == dirs[i])
            {
                while(item->childCount())
                {
                   item->removeChild(item->child(0));
                }
                ui->tree_dir->removeItemWidget(item,0);
                break;
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(_client.isNull())
    {
        _client.reset(new BaseClient(ui->serv_addr->text(),ui->serv_port->text().toInt()));
        connect(_client.get(),&BaseClient::connected_socket,this,[&]
        {
            ui->terminal->addItem("connected to " + ui->serv_addr->text() + ":" + ui->serv_port->text());
        });
        connect(_client.get(),&BaseClient::disconnected_socket,this,[&]
        {
            ui->terminal->addItem("disconnected from " + ui->serv_addr->text() + ":" + ui->serv_port->text());
        });
        connect(_client.get(),&BaseClient::socket_error,this,[&](QAbstractSocket::SocketError state)
        {
            ui->terminal->addItem("Error " + QString::number(state));
        });
        connect(_client.get(),&BaseClient::ready_data_read,this,&MainWindow::slot_ready_read);
    }
    if(_client->is_connected())
    {
        _client->disconnect_to_host();
    }
    else
    {
        _client->connect_to_host();
    }
}

void MainWindow::slot_ready_read()
{
    QByteArray data;
    _client->read_data(data);

    auto task = new TaskRecvMsg(&info_recv_data,data);
    connect(task,&TaskRecvMsg::recved_data,_client.get(),[&]()
    {
        ui->terminal->addItem(info_recv_data._msg);
        info_recv_data = {"",0,false};
    }, Qt::ConnectionType::DirectConnection);
    _proxy.push(task);
}

void MainWindow::on_send_button_clicked()
{
    auto temp = ui->input_line->text().toLatin1();
    auto task = new TaskSendMsg(temp,&_proxy);
    connect(task,&TaskSendMsg::send_data,_client.get(),[&](QByteArray array)
    {
        _client->write_data(array);
    }, Qt::ConnectionType::QueuedConnection);
    _proxy.push(task);
}

void MainWindow::on_select_path_button_clicked()
{
    auto dir = QFileDialog::getExistingDirectory(nullptr,"Выбор рабочей директории","",nullptr);
    if(!dir.isEmpty())
    {
        worker_meta_data.change_dir(dir);
    }
}


void MainWindow::on_scan_dir_button_clicked()
{
    worker_meta_data.scan_dir();
    QByteArray data;
    worker_meta_data.create_sended_data(data);

}

void MainWindow::slot_exec_file(const QModelIndex &index)
{
    if(index.isValid())
    {
        qDebug() << index;
    }
}
