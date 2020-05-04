#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDataStream>

#include <QThread>
#include <QMessageBox>
#include <QIcon>
#include <QMenu>
#include <QHeaderView>

const QColor MainWindow::TASK_COLOR = qRgb(65,105,225);
const QColor MainWindow::DEFAULT_COLOR = qRgb(255,255,255);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    worker_meta_data(&_proxy),
    _worker_remote_client(&_proxy)
{
    _proxy.start();
    ui->setupUi(this);

    connect(&_worker_remote_client,&WorkerRemoteClient::error_name_file,this,[]
    {
        QMessageBox::warning(nullptr,"Ошибка","Неверное имя файла");
    });
    connect(&_worker_remote_client,&WorkerRemoteClient::error_open_file,this,[]
    {
        QMessageBox::warning(nullptr,"Ошибка","Ошибка открытия файла");
    });
    connect(&_worker_remote_client,&WorkerRemoteClient::error_connect_to_host,this,[]
    {
        QMessageBox::warning(nullptr,"Ошибка","Ошибка подключения");
    });
    connect(&_worker_remote_client,&WorkerRemoteClient::error_didnt_found_file,this,[]
    {
        QMessageBox::warning(nullptr,"Ошибка","Файл на устройстве не найден");
    });
    connect(&_worker_remote_client,&WorkerRemoteClient::connect_to_host,this,[]
    {
        QMessageBox::information(nullptr,"Информация","Устройство подключено");
    });
    connect(&_worker_remote_client,&WorkerRemoteClient::downloaded_file,this,[]
    {
        QMessageBox::information(nullptr,"Информация","Файл скачен");
    });

    connect(ui->tree_dir,&QTreeWidget::doubleClicked,this,[this]
    {
        for(auto &item : _search_res)
        {
            item->setBackgroundColor(0,Qt::white);
        }
        _search_res.clear();
    });

    qRegisterMetaType<WorkerMetaData::MetaDataDir>("MetaDataDir");

    connect(&worker_meta_data,&WorkerMetaData::upload_tree,this,&MainWindow::slot_load_tree,Qt::ConnectionType::QueuedConnection);

    _settings.read_settings();

    auto name = _settings.get_name();

    _remote_dir.insert(name,qMakePair(0,ui->tree_dir));
    ui->users->addItem(name + ("(user)"));

    auto path = _settings.get_path();    

    ui->self_addr->setText(_settings.get_self_addr());
    ui->serv_addr->setText(_settings.get_serv_addr());

    ui->serv_port->setValue(_settings.get_serv_port());
    ui->self_port->setValue(_settings.get_self_port());

    worker_meta_data.load_data_from_database();
    worker_meta_data.scan_dir();

    ui->name_line->setText(name);
    ui->path_line->setText(path);

    ui->stack_widget->removeWidget(ui->remote_page);
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

        new_tree->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(new_tree,&QTreeWidget::customContextMenuRequested,this, &MainWindow::slot_sub_menu);
        connect(new_tree,&QTreeWidget::doubleClicked,this,[this]
        {
            for(auto &item : _search_res)
            {
                item->setBackgroundColor(0,Qt::white);
                _search_res.clear();
            }
        });

        new_tree->setHeaderItem(ui->tree_dir->headerItem()->clone());
        int index = ui->stack_widget->addWidget(new_tree);
        _remote_dir[name] = qMakePair(index,new_tree);

    }
    auto tree = _remote_dir.find(name)->second;
    tree->clear();
    add_dirs(tree, data.first);
    add_files(name,tree, data.second);
    _worker_remote_client.work_task(name);
}

void MainWindow::slot_sub_menu(const QPoint &pos)
{
    auto tree = static_cast<QTreeWidget*>(ui->stack_widget->currentWidget());
    auto item = tree->itemAt(pos);
    if(item && !item->text(1).isEmpty())
    {
        QMenu sub_menu;
        QAction *download = sub_menu.addAction("Скачать файл");

        QAction *tasks_option = nullptr;
        if(item->backgroundColor(0) != TASK_COLOR)
        {
            tasks_option = sub_menu.addAction("Добавить задачу");
            connect(tasks_option,&QAction::triggered,this,[this,item]
            {                
                if(slot_insert_task(item))
                {
                    item->setBackgroundColor(0,TASK_COLOR);
                }
            });
        }
        else
        {
            tasks_option = sub_menu.addAction("Снять задачу");
            connect(tasks_option,&QAction::triggered,this,[this,item]
            {
                if(slot_delete_task(item))
                {
                    item->setBackgroundColor(0,DEFAULT_COLOR);
                }

            });
        }

        connect(download,&QAction::triggered,this,[this, item]
        {
            slot_download_file(item);
        });

        sub_menu.exec(tree->mapToGlobal(pos));
    }
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

void MainWindow::add_files(const QString &name, QTreeWidget *tree, WorkerMetaData::FileMetaData &files)
{
    auto tasks_files = _settings.get_all_task_user(name).first.first;
    for(auto it = files.begin(); it != files.end(); it++)
    {
        bool is_tasks = false;
        if(tasks_files.indexOf(it.key()) != -1)
        {
            is_tasks = true;
        }
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
                if(is_tasks)
                {
                    name->setBackgroundColor(0,TASK_COLOR);
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
            worker_meta_data.scan_dir();
        });
        connect(_client.get(),&BaseClient::disconnected_socket,this,[&]
        {
            ui->statusBar->clearMessage();
            ui->serv_addr->setEnabled(true);
            ui->serv_port->setEnabled(true);
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
    worker_meta_data.scan_dir();
}

void MainWindow::on_work_serv_clicked()
{
    if(!_worker_remote_client.is_serv_run())
    {
        if(_worker_remote_client.run_serv())
        {
            ui->self_addr->setEnabled(false);
            ui->self_port->setEnabled(false);
        }
    }
    else
    {
        _worker_remote_client.stop_serv();
        ui->self_addr->setEnabled(true);
        ui->self_port->setEnabled(true);
    }
}

void MainWindow::slot_download_file(QTreeWidgetItem *item)
{
    auto index = ui->stack_widget->currentIndex();
    if(item && index)
    {
        if(!item->text(1).isEmpty())
        {
            QString file_name = item->text(0);
            QString path = get_absolute_path(item);
            while(item)
            {
                if(item->childCount())
                {
                    path.push_front(item->text(0) + '/');
                }
                else
                {
                    path.push_front(item->text(0));
                }
                item = item->parent();
            }
            auto dst = QFileDialog::getSaveFileName(nullptr,"Выберите место сохранения файла",file_name);
            if(!dst.isEmpty())
            {
                auto name = ui->users->item(index)->text();
                _worker_remote_client.download_file(path,dst,name);
            }
        }
    }
}

bool MainWindow::slot_insert_task(QTreeWidgetItem *item)
{
    auto index = ui->stack_widget->currentIndex();
    if(item && index)
    {
        if(!item->text(1).isEmpty())
        {
            QString file_name = item->text(0);
            QString path = get_absolute_path(item);
            auto dst = QFileDialog::getSaveFileName(nullptr,"Выберите место сохранения файла",file_name);
            if(!dst.isEmpty())
            {
                auto name = ui->users->item(index)->text();
                return _settings.insert_task_user(name,{path},{dst},{"null"});
            }
        }
    }
    return false;
}

bool MainWindow::slot_delete_task(QTreeWidgetItem *item)
{
    auto index = ui->stack_widget->currentIndex();
    if(item && index)
    {
        if(!item->text(1).isEmpty())
        {
            QString file_name = item->text(0);
            QString path = get_absolute_path(item);
            auto name = ui->users->item(index)->text();
            return _settings.delete_task_user(name,{path});
        }
    }
    return false;
}

QString MainWindow::get_absolute_path(QTreeWidgetItem *item)
{
    QString path;
    while(item)
    {
        path.push_front('/' + item->text(0));
        item = item->parent();
    }
    return path;
}


void MainWindow::on_search_button_clicked()
{
    QTreeWidget* tree = nullptr;
    if(ui->stack_widget->currentIndex())
    {
        tree = static_cast<QTreeWidget*>(ui->stack_widget->currentWidget());
    }
    else
    {
        tree = ui->tree_dir;
    }
    for(auto &item : _search_res)
    {
        item->setBackgroundColor(0,Qt::white);
    }
    _search_res = search_item(tree,ui->search_line->text());
    if(_search_res.empty())
    {
        QMessageBox::information(nullptr,"Информация","Объект не обнаружен");
    }
    for(auto &item : _search_res)
    {
        item->setBackgroundColor(0,Qt::red);
    }
}

void MainWindow::on_search_line_returnPressed()
{
    on_search_button_clicked();
}

QList<QTreeWidgetItem*> MainWindow::search_item(QTreeWidget* tree, const QString &text)
{
    if(!tree || text.isEmpty())
    {
        return {};
    }
    tree->setCurrentItem(nullptr);

    if(text[0] != '/')
    {
        return tree->findItems(text,Qt::MatchFlag::MatchRecursive);
    }

    auto path = text.split('/');
    path.removeAll("");

    QList<QTreeWidgetItem*> items;
    for(int i = 0; i < path.size(); i++)
    {
        auto cur = tree->currentItem();
        if(i + 1 == path.size())
        {
            if(!cur)
            {
               items = tree->findItems(path[i],Qt::MatchFlag::MatchFixedString);
            }
            else
            {
                for(int j = 0; j < cur->childCount(); j++)
                {
                    if(cur->child(j)->text(0) == path[i])
                    {
                        items.push_back(cur->child(j));
                    }
                }
            }
        }
        else
        {
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
    return items;
}
