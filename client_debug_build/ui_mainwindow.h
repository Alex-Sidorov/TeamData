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
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
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
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *main_tab;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QStackedWidget *stack_widget;
    QWidget *main_page;
    QHBoxLayout *horizontalLayout_6;
    QTreeWidget *tree_dir;
    QWidget *remote_page;
    QListWidget *users;
    QPushButton *pushButton_2;
    QWidget *option_tab;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QFrame *line_2;
    QLabel *label_3;
    QLineEdit *serv_addr;
    QLabel *label_4;
    QLineEdit *serv_port;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QFrame *line;
    QLabel *label_5;
    QLineEdit *self_addr;
    QLabel *label_8;
    QLineEdit *self_port;
    QPushButton *work_serv;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *name_line;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *path;
    QPushButton *select_path_button;
    QPushButton *scan_dir_button;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(748, 464);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        main_tab = new QWidget();
        main_tab->setObjectName(QString::fromUtf8("main_tab"));
        verticalLayout_3 = new QVBoxLayout(main_tab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        stack_widget = new QStackedWidget(main_tab);
        stack_widget->setObjectName(QString::fromUtf8("stack_widget"));
        main_page = new QWidget();
        main_page->setObjectName(QString::fromUtf8("main_page"));
        horizontalLayout_6 = new QHBoxLayout(main_page);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        tree_dir = new QTreeWidget(main_page);
        tree_dir->setObjectName(QString::fromUtf8("tree_dir"));
        tree_dir->header()->setCascadingSectionResizes(true);
        tree_dir->header()->setDefaultSectionSize(200);
        tree_dir->header()->setHighlightSections(true);

        horizontalLayout_6->addWidget(tree_dir);

        stack_widget->addWidget(main_page);
        remote_page = new QWidget();
        remote_page->setObjectName(QString::fromUtf8("remote_page"));
        stack_widget->addWidget(remote_page);

        horizontalLayout_3->addWidget(stack_widget);

        users = new QListWidget(main_tab);
        users->setObjectName(QString::fromUtf8("users"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(users->sizePolicy().hasHeightForWidth());
        users->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(users);


        verticalLayout_3->addLayout(horizontalLayout_3);

        pushButton_2 = new QPushButton(main_tab);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_3->addWidget(pushButton_2);

        tabWidget->addTab(main_tab, QString());
        option_tab = new QWidget();
        option_tab->setObjectName(QString::fromUtf8("option_tab"));
        verticalLayout_4 = new QVBoxLayout(option_tab);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(option_tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        line_2 = new QFrame(option_tab);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_2);

        label_3 = new QLabel(option_tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        serv_addr = new QLineEdit(option_tab);
        serv_addr->setObjectName(QString::fromUtf8("serv_addr"));

        horizontalLayout_2->addWidget(serv_addr);

        label_4 = new QLabel(option_tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        serv_port = new QLineEdit(option_tab);
        serv_port->setObjectName(QString::fromUtf8("serv_port"));

        horizontalLayout_2->addWidget(serv_port);


        verticalLayout_4->addLayout(horizontalLayout_2);

        pushButton = new QPushButton(option_tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_4->addWidget(pushButton);

        verticalSpacer_2 = new QSpacerItem(20, 81, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_7 = new QLabel(option_tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_5->addWidget(label_7);

        line = new QFrame(option_tab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(line);

        label_5 = new QLabel(option_tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        self_addr = new QLineEdit(option_tab);
        self_addr->setObjectName(QString::fromUtf8("self_addr"));

        horizontalLayout_5->addWidget(self_addr);

        label_8 = new QLabel(option_tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_5->addWidget(label_8);

        self_port = new QLineEdit(option_tab);
        self_port->setObjectName(QString::fromUtf8("self_port"));

        horizontalLayout_5->addWidget(self_port);


        verticalLayout_4->addLayout(horizontalLayout_5);

        work_serv = new QPushButton(option_tab);
        work_serv->setObjectName(QString::fromUtf8("work_serv"));

        verticalLayout_4->addWidget(work_serv);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(option_tab);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        name_line = new QLineEdit(option_tab);
        name_line->setObjectName(QString::fromUtf8("name_line"));

        horizontalLayout->addWidget(name_line);


        verticalLayout_4->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        path = new QLineEdit(option_tab);
        path->setObjectName(QString::fromUtf8("path"));

        horizontalLayout_4->addWidget(path);

        select_path_button = new QPushButton(option_tab);
        select_path_button->setObjectName(QString::fromUtf8("select_path_button"));

        horizontalLayout_4->addWidget(select_path_button);


        verticalLayout_4->addLayout(horizontalLayout_4);

        scan_dir_button = new QPushButton(option_tab);
        scan_dir_button->setObjectName(QString::fromUtf8("scan_dir_button"));

        verticalLayout_4->addWidget(scan_dir_button);

        tabWidget->addTab(option_tab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 748, 21));
        MainWindow->setMenuBar(menuBar);
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = tree_dir->headerItem();
        ___qtreewidgetitem->setText(3, QApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \321\201\320\276\320\267\320\264\320\260\320\275\320\270\321\217", nullptr));
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \320\277\320\276\321\201\320\273\320\265\320\264\320\275\320\265\320\271 \320\274\320\276\320\264\320\270\321\204\320\270\320\272\320\260\321\206\320\270\320\270", nullptr));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 \321\204\320\260\320\271\320\273\320\260", nullptr));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(main_tab), QApplication::translate("MainWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\320\270", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\320\241\320\265\321\200\320\262\320\265\321\200", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "IP \320\260\320\264\321\200\320\265\321\201:", nullptr));
        serv_addr->setText(QApplication::translate("MainWindow", "192.168.100.4", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202", nullptr));
        serv_port->setText(QApplication::translate("MainWindow", "8000", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "connect/disconnect", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "\320\241\320\262\320\276\320\271", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "IP \320\260\320\264\321\200\320\265\321\201:", nullptr));
        self_addr->setText(QApplication::translate("MainWindow", "192.168.100.4", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202", nullptr));
        self_port->setText(QApplication::translate("MainWindow", "80", nullptr));
        work_serv->setText(QApplication::translate("MainWindow", "start/stop", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\230\320\274\321\217:", nullptr));
        name_line->setText(QApplication::translate("MainWindow", "Alex", nullptr));
        path->setText(QApplication::translate("MainWindow", "D:\\\\dir", nullptr));
        select_path_button->setText(QApplication::translate("MainWindow", "...", nullptr));
        scan_dir_button->setText(QApplication::translate("MainWindow", "scan", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(option_tab), QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
