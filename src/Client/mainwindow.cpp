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

    qRegisterMetaType<WorkerMetaData::MetaDataDir>("MetaDataDir");

    connect(&worker_meta_data,&WorkerMetaData::upload_tree,this,&MainWindow::slot_load_tree,Qt::ConnectionType::QueuedConnection);

    /*auto name = ui->name_line->text();
    _remote_dir.insert(name,qMakePair(0,ui->tree_dir));
    ui->users->addItem(name + ("(user)"));

    worker_meta_data.change_name(name);
    worker_meta_data.change_dir("D:\\dir");
    worker_meta_data.scan_dir();*/
}

MainWindow::~MainWindow()
{
    for(auto &widget : _remote_dir)
    {
        if(widget.second != ui->tree_dir)
        {
            delete widget.second;
        }
    }
    delete ui;
}

void MainWindow::slot_load_tree(WorkerMetaData::MetaDataDir data, QString name)
{
    if(_remote_dir.find(name) == _remote_dir.end())
    {
        ui->users->addItem(name);
        auto new_tree = new QTreeWidget;
        new_tree->setHeaderItem(ui->tree_dir->headerItem()->clone());
        int index = ui->stack_widget->addWidget(new_tree);
        _remote_dir[name] = qMakePair(index,new_tree);

    }
    auto tree = _remote_dir.find(name)->second;
    tree->clear();
    add_dirs(tree, data.first);
    add_files(tree, data.second);
}

void MainWindow::add_dirs(QTreeWidget *tree, QStringList &dirs)
{
    for(auto it = dirs.begin(); it != dirs.end(); it++)
    {
        auto path = it->split('/');
        tree->setCurrentItem(nullptr);
        for(int i = 0; i < path.size(); i++)
        {
            if(!path[i].isEmpty())
            {
                auto cur = tree->currentItem();
                if(!cur)
                {
                    auto v = tree->findItems(path[i],Qt::MatchFlag::MatchFixedString);
                    if(v.size())
                    {
                        tree->setCurrentItem(v[0]);
                    }
                    else
                    {
                        auto name = new QTreeWidgetItem(QStringList(path[i]));
                        name->setIcon(0,QApplication::style()->standardIcon(QStyle::SP_DirIcon));
                        auto ptr = tree->currentItem();
                        if(ptr)
                        {
                            ptr->addChild(name);
                        }
                        else
                        {
                            tree->insertTopLevelItem(0,name);
                        }
                        tree->setCurrentItem(name);
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
                            tree->setCurrentItem(cur->child(j));
                            break;
                        }
                    }
                    if(!is_be)
                    {
                        auto name = new QTreeWidgetItem(QStringList(path[i]));
                        name->setIcon(0,QApplication::style()->standardIcon(QStyle::SP_DirIcon));
                        auto ptr = tree->currentItem();
                        if(ptr)
                        {
                            ptr->addChild(name);
                        }
                        else
                        {
                            tree->insertTopLevelItem(0,name);
                        }
                        tree->setCurrentItem(name);
                    }
                }
            }
        }
    }
    tree->setCurrentItem(nullptr);
}

void MainWindow::add_files(QTreeWidget *tree, WorkerMetaData::FileMetaData &files)
{
    for(auto it = files.begin(); it != files.end(); it++)
    {
        auto path = it.key().split('/');
        auto data = it.value();
        tree->setCurrentItem(nullptr);
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
                name->setText(2,std::get<2>(data));
                name->setText(3,std::get<1>(data));
                name->setIcon(0,QApplication::style()->standardIcon(QStyle::SP_FileIcon));
                auto ptr = tree->currentItem();
                if(ptr)
                {
                    ptr->addChild(name);
                }
                else
                {
                    tree->insertTopLevelItem(0,name);
                }
            }
            else
            {
                auto cur = tree->currentItem();
                if(!cur)
                {
                   tree->setCurrentItem(tree->findItems(path[i],Qt::MatchFlag::MatchFixedString)[0]);
                }
                else
                {
                    for(int j = 0; j < cur->childCount(); j++)
                    {
                        if(cur->child(j)->text(0) == path[i])
                        {
                            tree->setCurrentItem(cur->child(j));
                            break;
                        }
                    }
                }
            }
        }
    }
    tree->setCurrentItem(nullptr);
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
            ui->statusBar->showMessage("CONNECTED");
            //ui->terminal->addItem("connected to " + ui->serv_addr->text() + ":" + ui->serv_port->text());
        });
        connect(_client.get(),&BaseClient::disconnected_socket,this,[&]
        {
            ui->statusBar->clearMessage();
           // ui->terminal->addItem("disconnected from " + ui->serv_addr->text() + ":" + ui->serv_port->text());
        });
        connect(_client.get(),&BaseClient::socket_error,this,[&](QAbstractSocket::SocketError state)
        {
            //ui->terminal->addItem("Error " + QString::number(state));
        });

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

void MainWindow::on_users_doubleClicked(const QModelIndex &index)
{
    if(index.isValid())
    {
        auto text = ui->users->item(index.row())->text();
        auto name = text.mid(0,text.indexOf('('));
        auto index =_remote_dir[name].first;
        ui->stack_widget->setCurrentIndex(index);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    auto name = ui->name_line->text();
    _remote_dir.insert(name,qMakePair(0,ui->tree_dir));
    ui->users->addItem(name + ("(user)"));

    worker_meta_data.change_name(name);
    worker_meta_data.change_dir(ui->path->text());
    worker_meta_data.scan_dir();
}
