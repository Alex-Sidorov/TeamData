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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
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
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLabel *label_3;
    QLineEdit *serv_addr;
    QLabel *label_4;
    QLineEdit *serv_port;
    QPushButton *work_button;
    QHBoxLayout *horizontalLayout_3;
    QTreeWidget *tree_dir;
    QListWidget *terminal;
    QLineEdit *input_line;
    QPushButton *send_button;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(743, 477);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        serv_addr = new QLineEdit(centralWidget);
        serv_addr->setObjectName(QString::fromUtf8("serv_addr"));

        horizontalLayout_2->addWidget(serv_addr);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        serv_port = new QLineEdit(centralWidget);
        serv_port->setObjectName(QString::fromUtf8("serv_port"));

        horizontalLayout_2->addWidget(serv_port);


        verticalLayout->addLayout(horizontalLayout_2);

        work_button = new QPushButton(centralWidget);
        work_button->setObjectName(QString::fromUtf8("work_button"));

        verticalLayout->addWidget(work_button);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        tree_dir = new QTreeWidget(centralWidget);
        tree_dir->setObjectName(QString::fromUtf8("tree_dir"));
        tree_dir->header()->setCascadingSectionResizes(true);
        tree_dir->header()->setDefaultSectionSize(200);
        tree_dir->header()->setHighlightSections(true);

        horizontalLayout_3->addWidget(tree_dir);

        terminal = new QListWidget(centralWidget);
        terminal->setObjectName(QString::fromUtf8("terminal"));

        horizontalLayout_3->addWidget(terminal);


        verticalLayout->addLayout(horizontalLayout_3);

        input_line = new QLineEdit(centralWidget);
        input_line->setObjectName(QString::fromUtf8("input_line"));

        verticalLayout->addWidget(input_line);

        send_button = new QPushButton(centralWidget);
        send_button->setObjectName(QString::fromUtf8("send_button"));

        verticalLayout->addWidget(send_button);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 743, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\320\241\320\265\321\200\320\262\320\265\321\200|", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "IP \320\260\320\264\321\200\320\265\321\201:", nullptr));
        serv_addr->setText(QApplication::translate("MainWindow", "192.168.100.4", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202", nullptr));
        serv_port->setText(QApplication::translate("MainWindow", "8000", nullptr));
        work_button->setText(QApplication::translate("MainWindow", "start/stop", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = tree_dir->headerItem();
        ___qtreewidgetitem->setText(3, QApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \321\201\320\276\320\267\320\264\320\260\320\275\320\270\321\217", nullptr));
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \320\277\320\276\321\201\320\273\320\265\320\264\320\275\320\265\320\271 \320\274\320\276\320\264\320\270\321\204\320\270\320\272\320\260\321\206\320\270\320\270", nullptr));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 \321\204\320\260\320\271\320\273\320\260", nullptr));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217", nullptr));
        send_button->setText(QApplication::translate("MainWindow", "\320\236\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
