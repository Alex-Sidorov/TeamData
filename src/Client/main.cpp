#include "mainwindow.h"
#include <QApplication>

#include "FileSystemWatcher/filesystem_informer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*auto files = FileSystemWatcher::FileSystemInformer::get_files("D:\\dir");
    auto dc = FileSystemWatcher::FileSystemInformer::get_date_created_files(files);
    auto dlm = FileSystemWatcher::FileSystemInformer::get_date_last_modified_files(files);*/

    WindowClient w;
    w.show();
    return a.exec();
}
