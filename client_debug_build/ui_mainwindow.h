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
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_6;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *main_tab;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *search_line;
    QPushButton *search_button;
    QHBoxLayout *horizontalLayout_31;
    QStackedWidget *stack_widget;
    QWidget *main_page;
    QHBoxLayout *horizontalLayout_61;
    QTreeWidget *tree_dir;
    QWidget *remote_page;
    QListWidget *users;
    QWidget *option_tab;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QFrame *line_2;
    QLabel *label_3;
    QLineEdit *serv_addr;
    QLabel *label_4;
    QSpinBox *serv_port;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QFrame *line;
    QLabel *label_5;
    QLineEdit *self_addr;
    QLabel *label_8;
    QSpinBox *self_port;
    QPushButton *work_serv;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *name_line;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *path_line;
    QPushButton *select_path_button;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(752, 497);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_6 = new QHBoxLayout(widget1);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        widget2 = new QWidget(centralWidget);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_8 = new QHBoxLayout(widget2);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
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
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        search_line = new QLineEdit(main_tab);
        search_line->setObjectName(QString::fromUtf8("search_line"));

        horizontalLayout_7->addWidget(search_line);

        search_button = new QPushButton(main_tab);
        search_button->setObjectName(QString::fromUtf8("search_button"));

        horizontalLayout_7->addWidget(search_button);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setSpacing(6);
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        stack_widget = new QStackedWidget(main_tab);
        stack_widget->setObjectName(QString::fromUtf8("stack_widget"));
        main_page = new QWidget();
        main_page->setObjectName(QString::fromUtf8("main_page"));
        horizontalLayout_61 = new QHBoxLayout(main_page);
        horizontalLayout_61->setSpacing(0);
        horizontalLayout_61->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_61->setObjectName(QString::fromUtf8("horizontalLayout_61"));
        horizontalLayout_61->setContentsMargins(0, 0, 0, 0);
        tree_dir = new QTreeWidget(main_page);
        tree_dir->setObjectName(QString::fromUtf8("tree_dir"));
        tree_dir->header()->setCascadingSectionResizes(true);
        tree_dir->header()->setDefaultSectionSize(200);
        tree_dir->header()->setHighlightSections(true);

        horizontalLayout_61->addWidget(tree_dir);

        stack_widget->addWidget(main_page);
        remote_page = new QWidget();
        remote_page->setObjectName(QString::fromUtf8("remote_page"));
        stack_widget->addWidget(remote_page);

        horizontalLayout_31->addWidget(stack_widget);

        users = new QListWidget(main_tab);
        users->setObjectName(QString::fromUtf8("users"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(users->sizePolicy().hasHeightForWidth());
        users->setSizePolicy(sizePolicy);

        horizontalLayout_31->addWidget(users);


        verticalLayout_3->addLayout(horizontalLayout_31);

        tabWidget->addTab(main_tab, QString());
        option_tab = new QWidget();
        option_tab->setObjectName(QString::fromUtf8("option_tab"));
        verticalLayout_2 = new QVBoxLayout(option_tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
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

        serv_port = new QSpinBox(option_tab);
        serv_port->setObjectName(QString::fromUtf8("serv_port"));
        serv_port->setMaximum(65535);
        serv_port->setValue(0);

        horizontalLayout_2->addWidget(serv_port);


        verticalLayout_2->addLayout(horizontalLayout_2);

        pushButton = new QPushButton(option_tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        verticalSpacer_2 = new QSpacerItem(20, 81, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

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

        self_port = new QSpinBox(option_tab);
        self_port->setObjectName(QString::fromUtf8("self_port"));
        self_port->setMaximum(65535);
        self_port->setValue(0);

        horizontalLayout_5->addWidget(self_port);


        verticalLayout_2->addLayout(horizontalLayout_5);

        work_serv = new QPushButton(option_tab);
        work_serv->setObjectName(QString::fromUtf8("work_serv"));

        verticalLayout_2->addWidget(work_serv);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(option_tab);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        name_line = new QLineEdit(option_tab);
        name_line->setObjectName(QString::fromUtf8("name_line"));

        horizontalLayout->addWidget(name_line);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        path_line = new QLineEdit(option_tab);
        path_line->setObjectName(QString::fromUtf8("path_line"));

        horizontalLayout_4->addWidget(path_line);

        select_path_button = new QPushButton(option_tab);
        select_path_button->setObjectName(QString::fromUtf8("select_path_button"));

        horizontalLayout_4->addWidget(select_path_button);


        verticalLayout_2->addLayout(horizontalLayout_4);

        tabWidget->addTab(option_tab, QString());

        verticalLayout->addWidget(tabWidget);

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
        tabWidget->setTabText(tabWidget->indexOf(main_tab), QApplication::translate("MainWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\320\270", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\320\241\320\265\321\200\320\262\320\265\321\200", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "IP \320\260\320\264\321\200\320\265\321\201:", nullptr));
        serv_addr->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "connect/disconnect", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "\320\241\320\262\320\276\320\271", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "IP \320\260\320\264\321\200\320\265\321\201:", nullptr));
        self_addr->setText(QString());
        label_8->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202", nullptr));
        work_serv->setText(QApplication::translate("MainWindow", "start/stop", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\230\320\274\321\217:", nullptr));
        name_line->setText(QString());
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
