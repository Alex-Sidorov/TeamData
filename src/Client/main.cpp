#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include <workerremoteclient.h>
#include <ActiveObject/proxyactiveobject.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    /*ActiveObject::ProxyActiveObject proxy;
    proxy.start();
    WorkerRemoteClient worker(&proxy);
    worker.run_serv();


    return a.exec();*/

    MainWindow w;
    w.show();
    return a.exec();
}
