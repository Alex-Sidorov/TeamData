#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include <QFileSystemModel>
#include <QDirModel>
#include <QHostInfo>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    //QHostInfo info =QHostInfo::fromName("192.168.43.246");
    /*QDirModel model;
    QTreeView view;
    view.setModel(&model);
    view.setRootIndex(model.index("D://dir"));
    view.show();
    for(volatile double i = 0; i < 1000000000; i++);
    for(volatile double i = 0; i < 1000000000; i++);
    model.refresh();
    return a.exec();*/

    MainWindow w;
    w.show();
    return a.exec();
}
