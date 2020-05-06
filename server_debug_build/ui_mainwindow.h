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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLineEdit *serv_addr;
    QLabel *label_8;
    QLineEdit *serv_port;
    QPushButton *pushButton;
    QPushButton *work_button;
    QHBoxLayout *horizontalLayout_3;
    QListWidget *terminal;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(743, 477);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: rgb(216, 216, 216);\n"
"}\n"
""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(centralWidget);
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
        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QFont font;
        font.setPointSize(10);
        label_7->setFont(font);
        label_7->setStyleSheet(QString::fromUtf8("border: 1px ;\n"
"color : white;"));

        horizontalLayout_8->addWidget(label_7);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("border: 1px ;\n"
"color : white;"));

        horizontalLayout_4->addWidget(label_5);

        serv_addr = new QLineEdit(widget);
        serv_addr->setObjectName(QString::fromUtf8("serv_addr"));
        serv_addr->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border: 1px solid grey;\n"
"	border-radius: 4px;\n"
"	background : white;\n"
"}"));

        horizontalLayout_4->addWidget(serv_addr);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);
        label_8->setStyleSheet(QString::fromUtf8("border: 1px ;\n"
"color : white;"));

        horizontalLayout_4->addWidget(label_8);

        serv_port = new QLineEdit(widget);
        serv_port->setObjectName(QString::fromUtf8("serv_port"));
        serv_port->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border: 1px solid grey;\n"
"	border-radius: 4px;\n"
"	background : white;\n"
"}"));

        horizontalLayout_4->addWidget(serv_port);

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

        horizontalLayout_4->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout->addWidget(widget);

        work_button = new QPushButton(centralWidget);
        work_button->setObjectName(QString::fromUtf8("work_button"));
        work_button->setStyleSheet(QString::fromUtf8("QPushButton\n"
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

        verticalLayout->addWidget(work_button);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        terminal = new QListWidget(centralWidget);
        terminal->setObjectName(QString::fromUtf8("terminal"));
        terminal->setStyleSheet(QString::fromUtf8("background-color:rgb(88, 88, 88);\n"
"color:white;"));

        horizontalLayout_3->addWidget(terminal);


        verticalLayout->addLayout(horizontalLayout_3);

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
        label_7->setText(QApplication::translate("MainWindow", "\320\241\320\265\321\200\320\262\320\265\321\200 \320\274\320\265\321\202\320\260\320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "IP \320\260\320\264\321\200\320\265\321\201", nullptr));
        serv_addr->setText(QApplication::translate("MainWindow", "192.168.100.4", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202", nullptr));
        serv_port->setText(QApplication::translate("MainWindow", "8000", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217 \320\272 \321\201\320\265\321\200\320\262\320\265\321\200\321\203 ", nullptr));
        work_button->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214 \321\201\320\265\321\200\320\262\320\265\321\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
