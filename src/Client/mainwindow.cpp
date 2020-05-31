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

const QColor WindowClient::TASK_COLOR = qRgb(65,105,225);
const QColor WindowClient::DEFAULT_COLOR = qRgb(88, 88, 88);

WindowClient::WindowClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _worker_meta_data(&_proxy),
    _worker_remote_client(&_proxy)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":icons/icon.png"));

    _proxy.start();

    connect(&_worker_remote_client,&WorkRemoteDevice::WorkerRemoteClient::error_name_file,this,[]
    {

    });
    connect(&_worker_remote_client,&WorkRemoteDevice::WorkerRemoteClient::error_open_file,this,[]
    {

    });
    connect(&_worker_remote_client,&WorkRemoteDevice::WorkerRemoteClient::error_connect_to_host,this,[]
    {

    });
    connect(&_worker_remote_client,&WorkRemoteDevice::WorkerRemoteClient::error_didnt_found_file,this,[]
    {

    });
    connect(&_worker_remote_client,&WorkRemoteDevice::WorkerRemoteClient::connect_to_host,this,[]
    {

    });
    connect(&_worker_remote_client,&WorkRemoteDevice::WorkerRemoteClient::downloaded_file,this,[]
    {

    });

    connect(ui->tree_dir,&QTreeWidget::doubleClicked,this,[this]
    {
        for(auto &item : _search_res)
        {
            item->setBackgroundColor(0,DEFAULT_COLOR);
        }
        _search_res.clear();
    });

    qRegisterMetaType<WorkMetaDataOnClient::WorkerMetaData::MetaDataDir>("MetaDataDir");

    connect(&_worker_meta_data,&WorkMetaDataOnClient::WorkerMetaData::upload_tree,
            this,&WindowClient::slot_load_tree,Qt::ConnectionType::QueuedConnection);

    _settings.read_settings();

    auto name = _settings.get_name();

    _remote_dir.insert(name,qMakePair(0,ui->tree_dir));
    ui->users->addItem(name + ("(Пользователь)"));

    auto path = _settings.get_path();    

    ui->self_addr->setText(_settings.get_self_addr());
    ui->serv_addr->setText(_settings.get_serv_addr());

    ui->serv_port->setValue(_settings.get_serv_port());
    ui->self_port->setValue(_settings.get_self_port());

    _worker_meta_data.load_data_from_database();
    _worker_meta_data.scan_dir();

    ui->name_line->setText(name);
    ui->path_line->setText(path);

    ui->stack_widget->removeWidget(ui->remote_page);
}

WindowClient::~WindowClient()
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

void WindowClient::slot_load_tree(WorkMetaDataOnClient::WorkerMetaData::MetaDataDir data,
                                QString name)
{
    if(_remote_dir.find(name) == _remote_dir.end())
    {
        ui->users->addItem(name);
        auto new_tree = new QTreeWidget;

        new_tree->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(new_tree,&QTreeWidget::customContextMenuRequested,this, &WindowClient::slot_sub_menu);
        connect(new_tree,&QTreeWidget::doubleClicked,this,[this]
        {
            for(auto &item : _search_res)
            {
                item->setBackgroundColor(0,DEFAULT_COLOR);
            }
            _search_res.clear();
        });

        new_tree->setHeaderItem(ui->tree_dir->headerItem()->clone());
        new_tree->setStyleSheet(ui->tree_dir->styleSheet());
        int index = ui->stack_widget->addWidget(new_tree);
        _remote_dir[name] = qMakePair(index,new_tree);

    }
    auto tree = _remote_dir.find(name)->second;
    tree->clear();
    add_dirs(tree, data.first);
    add_files(name,tree, data.second);
    _worker_remote_client.work_task(name);
}

void WindowClient::slot_sub_menu(const QPoint &pos)
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

void WindowClient::add_dirs(QTreeWidget *tree, QStringList &dirs)
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

void WindowClient::add_files(const QString &name,
                           QTreeWidget *tree,
                           WorkMetaDataOnClient::WorkerMetaData::FileMetaData &files)
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

void WindowClient::slot_removed_dirs(QStringList dirs)
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

void WindowClient::on_pushButton_clicked()
{
    if(!_client.isNull() && _client->is_connected())
    {
        _client->disconnect_to_host();
        _client.reset();
    }
    else
    {        
        _client.reset(new BaseClient(_settings.get_serv_addr(),_settings.get_serv_port()));

        connect(_client.get(),&BaseClient::connected_socket,this,[&]
        {
            ui->statusBar->showMessage("Подключен к серверу");
            ui->pushButton->setText("Отключиться от сервера");
            ui->serv_addr->setEnabled(false);
            ui->serv_port->setEnabled(false);
            ui->name_line->setEnabled(false);
            _worker_meta_data.scan_dir();
        });
        connect(_client.get(),&BaseClient::disconnected_socket,this,[&]
        {
            ui->pushButton->setText("Подключиться к серверу");
            ui->statusBar->clearMessage();
            ui->serv_addr->setEnabled(true);
            ui->serv_port->setEnabled(true);
             ui->name_line->setEnabled(true);
        });
        _client->connect_to_host();
        _worker_meta_data.change_client(_client.data());

    }
}


void WindowClient::on_select_path_button_clicked()
{
    auto dir = QFileDialog::getExistingDirectory(nullptr,"Выбор рабочей директории","",nullptr);
    if(!dir.isEmpty())
    {
        ui->path_line->setText(dir);
        on_path_line_editingFinished();
    }
}

void WindowClient::on_users_doubleClicked(const QModelIndex &index)
{
    if(index.isValid())
    {
        auto text = ui->users->item(index.row())->text();
        auto name = text.mid(0,text.indexOf('('));
        auto index =_remote_dir[name].first;
        ui->stack_widget->setCurrentIndex(index);
    }
}

void WindowClient::on_name_line_editingFinished()
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
    name += "(Пользователь)";
    ui->users->item(0)->setText(name);
}

void WindowClient::on_self_addr_editingFinished()
{
    _settings.set_self_addr(ui->self_addr->text());
}

void WindowClient::on_serv_addr_editingFinished()
{
    _settings.set_serv_addr(ui->serv_addr->text());
}

void WindowClient::on_serv_port_valueChanged(int value)
{
    _settings.set_serv_port(value);
}

void WindowClient::on_self_port_valueChanged(int value)
{
    _settings.set_self_port(value);
}

void WindowClient::on_path_line_editingFinished()
{
    _settings.set_path(ui->path_line->text());
    _worker_meta_data.scan_dir();
}

void WindowClient::on_work_serv_clicked()
{
    if(!_worker_remote_client.is_serv_run())
    {
        if(_worker_remote_client.run_serv())
        {
            ui->work_serv->setText("Остановить личный сервер");
            ui->self_addr->setEnabled(false);
            ui->self_port->setEnabled(false);
        }
    }
    else
    {
        ui->work_serv->setText("Запустить личный сервер");
        _worker_remote_client.stop_serv();
        ui->self_addr->setEnabled(true);
        ui->self_port->setEnabled(true);
    }
}

void WindowClient::slot_download_file(QTreeWidgetItem *item)
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
                _worker_remote_client.download_file(path,dst,name);
            }
        }
    }
}

bool WindowClient::slot_insert_task(QTreeWidgetItem *item)
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

bool WindowClient::slot_delete_task(QTreeWidgetItem *item)
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

QString WindowClient::get_absolute_path(QTreeWidgetItem *item)
{
    QString path;
    while(item)
    {
        path.push_front('/' + item->text(0));
        item = item->parent();
    }
    return path;
}


void WindowClient::on_search_button_clicked()
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
        item->setBackgroundColor(0,DEFAULT_COLOR);
    }
    _search_res = search_item(tree,ui->search_line->text());
    if(_search_res.empty())
    {
        QMessageBox::information(this,"Информация","Объект не обнаружен");
    }
    for(auto &item : _search_res)
    {
        item->setBackgroundColor(0,Qt::red);
    }
}

void WindowClient::on_search_line_returnPressed()
{
    on_search_button_clicked();
}

QList<QTreeWidgetItem*> WindowClient::search_item(QTreeWidget* tree, const QString &text)
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

