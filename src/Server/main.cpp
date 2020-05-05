#include "mainwindow.h"
#include <QApplication>


#include <QTcpSocket>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*QTcpSocket *socket = new QTcpSocket;
    bool flag = false;
    QFile file("file.docx");
    bool f = file.open(QIODevice::WriteOnly);
    socket->connectToHost("192.168.100.4",80);
    socket->write("file.docx");
    socket->connect(socket,&QTcpSocket::readyRead,[&]
    {
        while(socket->bytesAvailable())
        {
            auto data = socket->readAll();
            if(!flag)
            {
                data = data.mid(4);
                flag = true;
            }
            file.write(data);
        }

    });

    return a.exec();*/

    WindowServer w;
    w.show();

    return a.exec();
}
