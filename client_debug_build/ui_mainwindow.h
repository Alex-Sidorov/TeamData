/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_11;
    QTabWidget *tabWidget;
    QWidget *main_tab;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *search_line;
    QPushButton *search_button;
    QHBoxLayout *horizontalLayout_9;
    QStackedWidget *stack_widget;
    QWidget *main_page;
    QHBoxLayout *horizontalLayout_6;
    QTreeWidget *tree_dir;
    QWidget *remote_page;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QListWidget *users;
    QWidget *option_tab;
    QVBoxLayout *verticalLayout_10;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *serv_addr;
    QLabel *label_4;
    QSpinBox *serv_port;
    QPushButton *pushButton;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_5;
    QLineEdit *self_addr;
    QLabel *label_8;
    QSpinBox *self_port;
    QPushButton *work_serv;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *name_line;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_11;
    QLineEdit *path_line;
    QPushButton *select_path_button;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(650, 508);
        QFont font;
        font.setPointSize(10);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../icon/icon.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: rgb(216, 216, 216);\n"
"}\n"
""));
        MainWindow->setToolButtonStyle(Qt::ToolButtonFollowStyle);
        MainWindow->setDocumentMode(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_11 = new QVBoxLayout(centralWidget);
        verticalLayout_11->setSpacing(0);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 2, 0, 0);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setFont(font);
        tabWidget->setStyleSheet(QString::fromUtf8("QTabBar::tab {\n"
"	\n"
"    background-color:rgb(255, 255, 255);\n"
"    border: 2px solid #C4C4C3;\n"
"    border-top-left-radius: 4px;\n"
"    border-top-right-radius: 4px;\n"
"    min-width:40ex;\n"
"    padding: 2px;\n"
"}\n"
"\n"
"QTabBar::tab:selected, QTabBar::tab:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #fafafa, stop: 0.4 #f4f4f4,\n"
"                                stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);\n"
"}"));
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(true);
        tabWidget->setTabBarAutoHide(false);
        main_tab = new QWidget();
        main_tab->setObjectName(QString::fromUtf8("main_tab"));
        main_tab->setStyleSheet(QString::fromUtf8("	border-radius: 4px;"));
        verticalLayout = new QVBoxLayout(main_tab);
        verticalLayout->setSpacing(5);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        search_line = new QLineEdit(main_tab);
        search_line->setObjectName(QString::fromUtf8("search_line"));
        search_line->setFont(font);
        search_line->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border: 1px solid grey;\n"
"	border-radius: 4px;\n"
"	background : white;\n"
"}"));

        horizontalLayout_7->addWidget(search_line);

        search_button = new QPushButton(main_tab);
        search_button->setObjectName(QString::fromUtf8("search_button"));
        search_button->setFont(font);
        search_button->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{ \n"
"	height:20;\n"
"	width:140;\n"
"	border: 1px solid grey;\n"
"	border-radius: 4px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}\n"
"\n"
"QPushButton::pressed {\n"
"    background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 rgb(251, 252, 255), stop: 1 #f6f7fa);\n"
"}\n"
""));

        horizontalLayout_7->addWidget(search_button);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        stack_widget = new QStackedWidget(main_tab);
        stack_widget->setObjectName(QString::fromUtf8("stack_widget"));
        main_page = new QWidget();
        main_page->setObjectName(QString::fromUtf8("main_page"));
        horizontalLayout_6 = new QHBoxLayout(main_page);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        tree_dir = new QTreeWidget(main_page);
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setItalic(true);
        font2.setWeight(75);
        font2.setKerning(true);
        font2.setStyleStrategy(QFont::PreferDefault);
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setItalic(true);
        font3.setUnderline(false);
        font3.setWeight(75);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setTextAlignment(3, Qt::AlignCenter);
        __qtreewidgetitem->setFont(3, font3);
        __qtreewidgetitem->setBackground(3, QColor(255, 255, 255));
        __qtreewidgetitem->setTextAlignment(2, Qt::AlignCenter);
        __qtreewidgetitem->setFont(2, font3);
        __qtreewidgetitem->setBackground(2, QColor(255, 255, 255));
        __qtreewidgetitem->setTextAlignment(1, Qt::AlignCenter);
        __qtreewidgetitem->setFont(1, font2);
        __qtreewidgetitem->setBackground(1, QColor(255, 255, 255));
        __qtreewidgetitem->setTextAlignment(0, Qt::AlignCenter);
        __qtreewidgetitem->setFont(0, font1);
        tree_dir->setHeaderItem(__qtreewidgetitem);
        tree_dir->setObjectName(QString::fromUtf8("tree_dir"));
        tree_dir->setStyleSheet(QString::fromUtf8("\n"
"QHeaderView::section\n"
" {\n"
"    background-color : qlineargradient(x1:1, y1:2, x2:1, y2:2,\n"
"                                      stop:0 rgb(71, 71, 71));\n"
"    color: white;\n"
"}\n"
"\n"
"QTreeView {\n"
"	background-color:rgb(88, 88, 88);\n"
"	color: white;\n"
"}\n"
"\n"
"QTreeView::item:selected:active {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #6a6ea9, stop: 1 #888dd9);\n"
"}\n"
"\n"
"QScrollBar:horizontal\n"
"{\n"
"max-height: 15px;\n"
"}\n"
"\n"
"QScrollBar:vertical\n"
"{\n"
"max-width: 15px;\n"
"}"));
        tree_dir->header()->setCascadingSectionResizes(true);
        tree_dir->header()->setDefaultSectionSize(200);
        tree_dir->header()->setHighlightSections(true);

        horizontalLayout_6->addWidget(tree_dir);

        stack_widget->addWidget(main_page);
        remote_page = new QWidget();
        remote_page->setObjectName(QString::fromUtf8("remote_page"));
        stack_widget->addWidget(remote_page);

        horizontalLayout_9->addWidget(stack_widget);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_2 = new QLabel(main_tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMaximumSize(QSize(16777215, 23));
        QFont font4;
        font4.setPointSize(10);
        font4.setBold(true);
        font4.setWeight(75);
        label_2->setFont(font4);
        label_2->setStyleSheet(QString::fromUtf8("background-color:qlineargradient(x1:1, y1:2, x2:1, y2:2,\n"
"                                      stop:0 rgb(71, 71, 71));;\n"
"color : white;"));
        label_2->setTextFormat(Qt::AutoText);
        label_2->setScaledContents(false);
        label_2->setAlignment(Qt::AlignCenter);
        label_2->setWordWrap(false);
        label_2->setOpenExternalLinks(false);

        verticalLayout_3->addWidget(label_2);

        users = new QListWidget(main_tab);
        users->setObjectName(QString::fromUtf8("users"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(users->sizePolicy().hasHeightForWidth());
        users->setSizePolicy(sizePolicy1);
        users->setMinimumSize(QSize(10, 0));
        users->setMaximumSize(QSize(140, 16777215));
        users->setStyleSheet(QString::fromUtf8("QListView\n"
"{\n"
"background:rgb(27, 27, 27);\n"
"color:white;\n"
"}\n"
"\n"
"QListView::item:selected:active {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #6a6ea9, stop: 1 #888dd9);\n"
"}\n"
"\n"
""));
        users->setViewMode(QListView::ListMode);

        verticalLayout_3->addWidget(users);


        horizontalLayout_9->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout_9);

        tabWidget->addTab(main_tab, QString());
        option_tab = new QWidget();
        option_tab->setObjectName(QString::fromUtf8("option_tab"));
        verticalLayout_10 = new QVBoxLayout(option_tab);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        widget = new QWidget(option_tab);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border: 1px solid grey;\n"
"	border-radius: 4px;\n"
"	background-color:rgb(109, 109, 109);\n"
"}\n"
""));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8("border: 1px ;\n"
"color : white;"));

        horizontalLayout_8->addWidget(label_6);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("border: 1px ;\n"
"color : white;"));

        horizontalLayout_2->addWidget(label_3);

        serv_addr = new QLineEdit(widget);
        serv_addr->setObjectName(QString::fromUtf8("serv_addr"));
        serv_addr->setFont(font);
        serv_addr->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	height:20;\n"
"	border: 1px solid grey;\n"
"	border-radius: 4px;\n"
"	background : white;\n"
"}"));

        horizontalLayout_2->addWidget(serv_addr);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("border: 1px ;\n"
"color : white;"));

        horizontalLayout_2->addWidget(label_4);

        serv_port = new QSpinBox(widget);
        serv_port->setObjectName(QString::fromUtf8("serv_port"));
        serv_port->setFont(font);
        serv_port->setStyleSheet(QString::fromUtf8("border-color:white;\n"
"color : white;\n"
"height:20px;"));
        serv_port->setMaximum(65535);
        serv_port->setValue(0);

        horizontalLayout_2->addWidget(serv_port);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setFont(font);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{ \n"
"	height:20;\n"
"	width:200;\n"
"	border: 1px solid grey;\n"
"	border-radius: 4px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}\n"
"\n"
"QPushButton::pressed {\n"
"    background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 rgb(251, 252, 255), stop: 1 #f6f7fa);\n"
"}\n"
""));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_10->addWidget(widget);

        widget_3 = new QWidget(option_tab);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border: 1px solid grey;\n"
"	border-radius: 4px;\n"
"	background-color:rgb(109, 109, 109);\n"
"}\n"
""));
        verticalLayout_7 = new QVBoxLayout(widget_3);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_7 = new QLabel(widget_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);
        label_7->setStyleSheet(QString::fromUtf8("border: 1px ;\n"
"color : white;"));

        horizontalLayout_5->addWidget(label_7);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_5 = new QLabel(widget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("border: 1px ;\n"
"color : white;"));

        horizontalLayout_10->addWidget(label_5);

        self_addr = new QLineEdit(widget_3);
        self_addr->setObjectName(QString::fromUtf8("self_addr"));
        self_addr->setFont(font);
        self_addr->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	height:20;\n"
"	border: 1px solid grey;\n"
"	border-radius: 4px;\n"
"	background : white;\n"
"}"));

        horizontalLayout_10->addWidget(self_addr);

        label_8 = new QLabel(widget_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);
        label_8->setStyleSheet(QString::fromUtf8("border: 1px ;\n"
"color : white;"));

        horizontalLayout_10->addWidget(label_8);

        self_port = new QSpinBox(widget_3);
        self_port->setObjectName(QString::fromUtf8("self_port"));
        self_port->setFont(font);
        self_port->setStyleSheet(QString::fromUtf8("border-color:white;\n"
"color : white;\n"
"height:20px;"));
        self_port->setMaximum(65535);
        self_port->setValue(0);

        horizontalLayout_10->addWidget(self_port);

        work_serv = new QPushButton(widget_3);
        work_serv->setObjectName(QString::fromUtf8("work_serv"));
        work_serv->setFont(font);
        work_serv->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{ \n"
"	height:20;\n"
"	width:200;\n"
"	border: 1px solid grey;\n"
"	border-radius: 4px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}\n"
"\n"
"QPushButton::pressed {\n"
"    background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 rgb(251, 252, 255), stop: 1 #f6f7fa);\n"
"}\n"
""));

        horizontalLayout_10->addWidget(work_serv);


        verticalLayout_4->addLayout(horizontalLayout_10);


        verticalLayout_7->addLayout(verticalLayout_4);


        verticalLayout_10->addWidget(widget_3);

        widget_2 = new QWidget(option_tab);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border: 1px solid grey;\n"
"	border-radius: 4px;\n"
"	background-color:rgb(109, 109, 109);\n"
"}\n"
""));
        verticalLayout_8 = new QVBoxLayout(widget_2);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("border: 1px ;\n"
"color : white;"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_5->addLayout(horizontalLayout);

        name_line = new QLineEdit(widget_2);
        name_line->setObjectName(QString::fromUtf8("name_line"));
        name_line->setFont(font);
        name_line->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	height:20;\n"
"	border: 1px solid grey;\n"
"	border-radius: 4px;\n"
"	background : white;\n"
"}"));

        verticalLayout_5->addWidget(name_line);


        verticalLayout_8->addLayout(verticalLayout_5);


        verticalLayout_10->addWidget(widget_2);

        widget_4 = new QWidget(option_tab);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border: 1px solid grey;\n"
"	border-radius: 4px;\n"
"	background-color:rgb(109, 109, 109);\n"
"}\n"
""));
        verticalLayout_9 = new QVBoxLayout(widget_4);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_9 = new QLabel(widget_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);
        label_9->setStyleSheet(QString::fromUtf8("border: 1px ;\n"
"color : white;"));

        horizontalLayout_4->addWidget(label_9);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_6->addLayout(horizontalLayout_4);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        path_line = new QLineEdit(widget_4);
        path_line->setObjectName(QString::fromUtf8("path_line"));
        path_line->setFont(font);
        path_line->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	height:20;\n"
"	border: 1px solid grey;\n"
"	border-radius: 4px;\n"
"	background : white;\n"
"}"));

        horizontalLayout_11->addWidget(path_line);

        select_path_button = new QPushButton(widget_4);
        select_path_button->setObjectName(QString::fromUtf8("select_path_button"));
        select_path_button->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{ \n"
"	height:20;\n"
"	width:150;\n"
"	border: 1px solid grey;\n"
"	border-radius: 4px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}\n"
"\n"
"QPushButton::pressed {\n"
"    background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 rgb(251, 252, 255), stop: 1 #f6f7fa);\n"
"}\n"
""));

        horizontalLayout_11->addWidget(select_path_button);


        verticalLayout_6->addLayout(horizontalLayout_11);


        verticalLayout_9->addLayout(verticalLayout_6);


        verticalLayout_10->addWidget(widget_4);

        tabWidget->addTab(option_tab, QString());

        verticalLayout_11->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        stack_widget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "TeamData", nullptr));
        search_line->setPlaceholderText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272 (\320\260\320\261\321\201\320\276\320\273\321\216\321\202\320\275\321\213\320\271 \320\277\321\203\321\202\321\214 \320\275\320\260\321\207\320\270\320\275\320\260\320\265\321\202\321\201\321\217 \321\201 ' /  ' )", nullptr));
        search_button->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = tree_dir->headerItem();
        ___qtreewidgetitem->setText(3, QApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \321\201\320\276\320\267\320\264\320\260\320\275\320\270\321\217", nullptr));
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \320\277\320\276\321\201\320\273\320\265\320\264\320\275\320\265\320\271 \320\274\320\276\320\264\320\270\321\204\320\270\320\272\320\260\321\206\320\270\320\270", nullptr));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 \321\204\320\260\320\271\320\273\320\260", nullptr));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\320\270</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(main_tab), QApplication::translate("MainWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\320\270", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\320\241\320\265\321\200\320\262\320\265\321\200 \320\274\320\265\321\202\320\260\320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "IP \320\260\320\264\321\200\320\265\321\201", nullptr));
        serv_addr->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217 \320\272 \321\201\320\265\321\200\320\262\320\265\321\200\321\203 ", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "\320\233\320\270\321\207\320\275\321\213\320\271 \321\201\320\265\321\200\320\262\320\265\321\200", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "IP \320\260\320\264\321\200\320\265\321\201", nullptr));
        self_addr->setText(QString());
        label_8->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202", nullptr));
        work_serv->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214 \320\273\320\270\321\207\320\275\321\213\320\271 \321\201\320\265\321\200\320\262\320\265\321\200", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        name_line->setText(QString());
        label_9->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\261\320\276\321\207\320\260\321\217 \320\264\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217", nullptr));
        path_line->setText(QString());
        select_path_button->setText(QApplication::translate("MainWindow", "...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(option_tab), QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
