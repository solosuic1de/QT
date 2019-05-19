#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <loginwindow.h>
#include <QSqlQuery>
#include <QSqlDatabase>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QSqlDatabase db = QSqlDatabase::addDatabase(("QSQLITE"));
    db.setDatabaseName("/home/solosuicide133/Desktop/kursech/server/users/users");
    if(!db.open())
    {
        qDebug()<<"Failed to open database";
        return false;
    }
    else
        qDebug()<<"Connected to users db";

    loginWindow window;
    window.setDb(db);
    window.show();
    return a.exec();
}
