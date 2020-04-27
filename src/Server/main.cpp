#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //WorkerServerDataBase w1;
    //w1.delete_data_dir_user("Alex");

    MainWindow w;
    w.show();

    return a.exec();
}
