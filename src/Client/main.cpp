#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStyle>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    /*QTreeWidget *treeWidget = new QTreeWidget();
    treeWidget->setColumnCount(1);
    QList<QTreeWidgetItem *> items;
    for (int i = 0; i < 10; ++i)
    {
        items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
        QList<QTreeWidgetItem *> files;
        for (int j = 0; j < 5; j++)
        {
            files.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("file: %1").arg(i))));
            files.last()->setIcon(0,QApplication::style()->standardIcon(QStyle::SP_FileIcon));
        }
        items.last()->insertChildren(0,files);
        items.last()->setIcon(0,QApplication::style()->standardIcon(QStyle::SP_DirIcon));
    }
    treeWidget->insertTopLevelItems(0, items);
    treeWidget->setCurrentItem(items[0]);
    auto t = treeWidget->findItems("file: 1",Qt::MatchFlag::MatchCaseSensitive);
    treeWidget->show();
    return a.exec();*/

    MainWindow w;
    w.show();
    return a.exec();
}
