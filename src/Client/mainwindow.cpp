#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDataStream>

#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    worker_meta_data(&_proxy)
{
    _proxy.start();
    ui->setupUi(this);

    connect(&worker_meta_data,&WorkerMetaData::upload_tree,this,&MainWindow::slot_load_tree);

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
    ui->tree_dir->setCurrentItem(nullptr);
}

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
                item->parent()->removeChild(item);
                delete item;
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
            //ui->terminal->addItem("connected to " + ui->serv_addr->text() + ":" + ui->serv_port->text());
        });
        connect(_client.get(),&BaseClient::disconnected_socket,this,[&]
        {
           // ui->terminal->addItem("disconnected from " + ui->serv_addr->text() + ":" + ui->serv_port->text());
        });
        connect(_client.get(),&BaseClient::socket_error,this,[&](QAbstractSocket::SocketError state)
        {
            //ui->terminal->addItem("Error " + QString::number(state));
        });

        worker_meta_data.change_name(ui->name_line->text());
        worker_meta_data.change_client(_client.data());
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

}
