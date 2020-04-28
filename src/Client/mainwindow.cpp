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

    _settings.read_settings();

    auto name = _settings.get_name();

    ui->name_line->setText(name);
    _remote_dir.insert(name,qMakePair(0,ui->tree_dir));
    ui->users->addItem(name + ("(user)"));

    auto path = _settings.get_path();
    ui->path_line->setText(path);

    ui->self_addr->setText(_settings.get_self_addr());
    ui->serv_addr->setText(_settings.get_serv_addr());

    ui->serv_port->setValue(_settings.get_serv_port());
    ui->self_port->setValue(_settings.get_self_port());

    worker_meta_data.scan_dir();
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
        _client.reset(new BaseClient(_settings.get_serv_addr(),_settings.get_serv_port()));

        connect(_client.get(),&BaseClient::connected_socket,this,[&]
        {
            ui->statusBar->showMessage("CONNECTED");
            ui->serv_addr->setEnabled(false);
            ui->serv_port->setEnabled(false);
            //ui->terminal->addItem("connected to " + ui->serv_addr->text() + ":" + ui->serv_port->text());
        });
        connect(_client.get(),&BaseClient::disconnected_socket,this,[&]
        {
            ui->statusBar->clearMessage();
            ui->serv_addr->setEnabled(true);
            ui->serv_port->setEnabled(true);
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
        _client.reset();   
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
        ui->path_line->setText(dir);
        on_path_line_editingFinished();
        worker_meta_data.change_dir(dir);
    }
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

void MainWindow::on_name_line_editingFinished()
{
    auto name = ui->name_line->text();

    auto text = ui->users->item(0)->text();
    auto old_name = text.mid(0,text.indexOf('('));
    if(_remote_dir.find(name) != _remote_dir.end())
    {
        ui->name_line->setText(old_name);
        return;
    }
    auto data = _remote_dir[old_name];
    _remote_dir.remove(old_name);


    _remote_dir.insert(name,data);

    _settings.set_name(name);
    worker_meta_data.change_name(name);
    name += "(user)";
    ui->users->item(0)->setText(name);
}

void MainWindow::on_self_addr_editingFinished()
{
    _settings.set_self_addr(ui->self_addr->text());
}

void MainWindow::on_serv_addr_editingFinished()
{
    _settings.set_serv_addr(ui->serv_addr->text());
}

void MainWindow::on_serv_port_valueChanged(int value)
{
    _settings.set_serv_port(value);
}

void MainWindow::on_self_port_valueChanged(int value)
{
    _settings.set_self_port(value);
}

void MainWindow::on_path_line_editingFinished()
{
    _settings.set_path(ui->path_line->text());
}
