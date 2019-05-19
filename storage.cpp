#include "storage.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <book.h>
#include <readerwindow.h>
storage::storage()
{

}
QByteArray storage::bookPic(int id)
{
    QSqlQuery * q =  new QSqlQuery(db);
    q->prepare("select * from Book where id =:id");
    q->bindValue(":id", id);
    q->exec();
    q->first();
    QByteArray pic = q->value(7).toByteArray();
    return pic;
}
void storage::updrole(int id, int role)
{
    QSqlQuery * q = new QSqlQuery(db);
    q->prepare("update users set role = :role where id=:id");
    q->bindValue(":role" , role);
    q->bindValue(":id" , id);
    q->exec();
}
void storage::addReader(QString login, QString password, QString name, QString surN, QString status)
{
    QSqlQuery qry(db);
    qry.prepare("insert into userInfo (Name, Surname, Status) values(:name, :surN, :status)");
    qry.prepare("insert into users (login,password_hash) values(:login,:password)");
    qry.bindValue(":login", login);
    qry.bindValue(":password", password);
    qry.exec();
    qry.clear();
    qry.prepare("insert into userInfo (Name, Surname, Status, id, Card) values(:name, :surname, :status, (select id from users where login = :login), (select id from users where login = :login))");
    qry.bindValue(":login", login);
    qry.bindValue(":name", name);
    qry.bindValue(":surname", surN);
    qry.bindValue(":status", status);
    qry.exec();
    //=============================================================================================
    qry.clear();
    qry.prepare("update users set userInfoId = (select id from users where login =:login) where login = :login");
    qry.bindValue(":login", login);
    qry.exec();
}
void storage::orderBtn(QString status, QString start, QString end, int id, QString name, QString author, QString genre, double rating, QString publisher, int year, int userID)
{
    QSqlQuery * q = new QSqlQuery(db);
    q->prepare("insert into Orders (start, status, bookId, end,userId) values(:start, :status, :bookId, :end, :userId)");
    q->bindValue(":status", status);
    q->bindValue(":start", start);
    q->bindValue(":bookId", id);
    q->bindValue(":end", end);
    q->bindValue(":userId", userID);
    q->exec();
    q->clear();
    q->prepare("update Book set name = :name, author=:author,genre=:genre,rating=:rating,publisher=:publisher,year=:year, status=:status where id=:id");
    q->bindValue(":name", name);
    q->bindValue(":author", author);
    q->bindValue(":genre", genre);
    q->bindValue(":rating", rating);
    q->bindValue(":publisher", publisher);
    q->bindValue(":year", year);
    q->bindValue(":id", id);
    q->bindValue(":status", "waiting");
    q->exec();
}
int storage::getBookIdfromOrd(int id)
{
    QSqlQuery * q = new QSqlQuery(db);
    q->prepare("select bookId from Orders where id =:id");
    q->bindValue(":id", id);
    q->exec();
    q->first();
    int ind =  q->value(0).toInt();
    return ind;
}
QString storage::getBookName(int id)
{
    QSqlQuery * q =  new QSqlQuery(db);
    q->prepare("select * from Book where id =(select bookId from Orders where id =:id)");
    q->bindValue(":id", id);
    q->exec();
    q->first();
    return q->value(1).toString();
}
void storage::editUsers(QString name, QString surN, int id, QString status)
{
    QSqlQuery * q = new QSqlQuery(db);
    q->prepare("update userInfo set Name = :name, Surname=:Surname,Status=:Status where id=:id");
    q->bindValue(":name", name);
    q->bindValue(":Surname", surN);
    q->bindValue(":id", id);
    q->bindValue(":Status", status);
    q->exec();
    q->clear();
}
void storage::edit(QString name, QString author, QString publisher, QString genre, double rating, int year, int id, QString status)
{
    QSqlQuery q(db);
    q.prepare("update Book set name = :name, author=:author,genre=:genre,rating=:rating,publisher=:publisher,year=:year, status=:status where id=:id");
    q.bindValue(":name", name);
    q.bindValue(":author", author);
    q.bindValue(":genre", genre);
    q.bindValue(":rating", rating);
    q.bindValue(":publisher", publisher);
    q.bindValue(":year", year);
    q.bindValue(":id", id);
    q.bindValue(":status", status);
    q.exec();
}
QList <QString> storage::getOrdN(int id)
{
    QList <QString> list;
    QSqlQuery * q =  new QSqlQuery(db);
    q->prepare("select * from userInfo where id =(select userId from Orders where id =:id)");
    q->bindValue(":id", id);
    q->exec();
    q->first();
    list.append(q->value(1).toString());
    list.append(q->value(2).toString());
    list.append(q->value(3).toString());
    return list;
}
QString storage::getN(int id)
{
    QSqlQuery * q =  new QSqlQuery(db);
    q->prepare("select * from userInfo where id =(select userId from Orders where id =:id)");
    q->bindValue(":id", id);
    q->exec();
    q->first();
    QString name = q->value(1).toString();
    return name;
}


UserInfo storage::loadUser(QString name, QString surname, QString status, int cardNum, int id){
    QSqlQuery * q = new QSqlQuery(db);
    q->prepare("SELECT * FROM users WHERE id = :id");
    q->bindValue(":id", id);
    q->exec();
    q->first();
    QString login = q->value(1).toString();
    int role = q->value(3).toInt();
    //qDebug()<<login + role;
    UserInfo  user(cardNum, name, surname, status, login, role);
    return user;
}
QList<orders> storage::showAllOrd()
{
    adminmenu w;
    int num_rows;

    QSqlQuery * q = new QSqlQuery(db);
    q->exec("select count(id) as num_rows from Orders");
    q->first();
    num_rows = q->value(0).toInt();
    w.setRowC(1, num_rows);
    q->prepare("select * from Orders");
    q->exec();
    QList<orders> list;
    while( q->next() ) {
        int id = q->value(0).toInt();
        QString start = q->value(1).toString();
        QString end = q->value(2).toString();
        QString status = q->value(3).toString();
        int bookId = q->value(4).toInt();
        int userId = q->value(5).toInt();
        orders order(id, start, end, status, bookId, userId);
        list.append(order);
    }
    return list;
}
void storage::cinform(int card, QString name, QString surn, QString status)
{
    QSqlQuery * q = new QSqlQuery(db);
    q->prepare("update userInfo set Name = :name, Surname=:Surname,Status=:Status where id=:id");
    q->bindValue(":name", name);
    q->bindValue(":Surname", surn);
    q->bindValue(":id", card);
    q->bindValue(":Status", status);
    q->exec();
}
QList<orders> storage::showOrders(int id)
{
    readerwindow w;
    int num_rows;
    QSqlQuery * q = new QSqlQuery(db);
    q->prepare("select count(id) as num_rows from Orders where userId =:id");
    q->bindValue(":id", id);
    q->exec();// QMessageBox::critical(this, "Database", q->lastError().text());
    q->first();
    num_rows = q->value(0).toInt();
    w.setRowCount(num_rows);
    //   ui->erdered->setRowCount(num_rows);
    q->prepare("select * from Orders where userId = :id");
    q->bindValue(":id", id);
    QList<orders> list;
    while( q->next() ) {
        int id = q->value(0).toInt();
        QString start = q->value(1).toString();
        QString end = q->value(2).toString();
        QString status = q->value(3).toString();
        int bookId = q->value(4).toInt();
        int userId = q->value(5).toInt();
        orders order(id, start, end, status, bookId, userId);
        list.append(order);
    }
    return list;
}
QList<orders> storage::showActiveOrd()
{
    adminmenu w;

    int num_rows;
    QSqlQuery * q = new QSqlQuery(db);
    q->prepare("select count(id) as num_rows from Orders where status =:status or status=:st");
    QString status = "waiting";
    QString st = "Accepted";
    q->bindValue(":status", status);
    q->bindValue(":st", st);
    q->exec();
    q->first();
    num_rows = q->value(0).toInt();
    w.setRowC(1, num_rows);
    q->prepare("select * from Orders where status =:status or status=:st");
    q->bindValue(":status", status);
    q->bindValue(":st", st);
    q->exec();
    QList<orders> list;
    while( q->next() ) {
        int id = q->value(0).toInt();
        QString start = q->value(1).toString();
        QString end = q->value(2).toString();
        QString status = q->value(3).toString();
        int bookId = q->value(4).toInt();
        int userId = q->value(5).toInt();
        orders order(id, start, end, status, bookId, userId);
        list.append(order);
    }
    return list;
}
QList<orders> storage::DeclineOrder(int id, QString status){
    if(status == "waiting")
    {
        qDebug()<<status;
        QSqlQuery * q = new QSqlQuery(db);
        q->prepare("select * from Orders where userId=:id and status =:status");
        q->bindValue(":id", id);
        q->bindValue(":status","Accepted");
        q->exec();
        if(q->size() == 0)
        {
            q->clear();
            q->prepare("update userInfo set Status=:Status where id = (select userId from Orders where id=:id)");
            q->bindValue(":id", id);
            q->bindValue(":Status", "Not debtor");
            q->exec();

        }
        q->clear();
        q->prepare("update Book set status =:Status where id = (select bookId from Orders where id =:id)");
        q->bindValue(":id", id);
        QString s = "Available";
        q->bindValue(":Status", s);
        q->exec();
        q->clear();
        q->prepare("update Orders set status =:name where id=:id");
        q->bindValue(":name", "Decline");
        q->bindValue(":id", id);
        q->exec();

    }

}
void storage::CloseOrder(int id, QString status, int ordid)
{
    //if(status == "Accepted")
    {
        qDebug()<<status;
        QSqlQuery * q = new QSqlQuery(db);
        q->prepare("select * from Orders where userId=:id and status =:status");
        q->bindValue(":id", id);
        q->bindValue(":status","Accepted");
        if(!q->exec()) qDebug()<<"1";
        if(q->size() < 1)
        {
            q->clear();
            q->prepare("update userInfo set Status=:Status where id = (select userId from Orders where id=:id)");
            q->bindValue(":id", ordid);
            q->bindValue(":Status", "Not debtor");
            q->exec();
        }
        q->clear();
        q->prepare("update Book set status =:Status where id = (select bookId from Orders where id =:id)");
        q->bindValue(":id", ordid);
        QString s = "Available";
        q->bindValue(":Status", s);
        if(!q->exec()) qDebug()<<"2";
        q->clear();
        q->prepare("update Orders set status =:name, end =:end where id=:id");
        q->bindValue(":name", "Closed");
        q->bindValue(":end", QDateTime::currentDateTime().toString(Qt::ISODate));
        q->bindValue(":id", ordid);
        if(!q->exec()) qDebug()<<"3";

    }

}
void storage::Accepted(int id, QString status)
{
    if(status == "waiting")
    {
        //  qDebug()<<status;
        QSqlQuery * q = new QSqlQuery(db);
        q->clear();
        q->prepare("update userInfo set Status=:Status where id = (select userId from Orders where id=:id)");
        q->bindValue(":id", id);
        q->bindValue(":Status", "Debtor");
        q->exec();
        q->clear();
        q->prepare("update Book set status =:Status where id = (select bookId from Orders where id =:id)");
        q->bindValue(":id", id);
        QString s = "Unavailable";
        q->bindValue(":Status", s);
        q->exec();
        q->clear();
        q->prepare("update Orders set status =:name where id=:id");
        q->bindValue(":name", "Accepted");
        q->bindValue(":id", id);
        q->exec();
    }

}
QList<book> storage::searchBook(QString string)
{
    adminmenu w;

    QList<book> list;
    int num_rows;
    QSqlQuery * q = new QSqlQuery(db);
    q->prepare("select count(id) as num_rows from Book where name =:genre");
    q->bindValue(":genre", string);
    q->exec();
    q->first();
    num_rows = q->value(0).toInt();
    w.setRowC(2, num_rows);
    q->prepare("select * from Book where name =:genre");
    q->bindValue(":genre", string);

    q->exec();
    while( q->next() ) {
        int id = q->value(0).toInt();
        QString name = q->value(1).toString();
        QString author = q->value(2).toString();
        QString genre = q->value(3).toString();
        double ratign = q->value(4).toDouble();
        QString publ = q->value(5).toString();
        int year = q->value(6).toInt();
        QString status = q->value(7).toString();
        book kniga(genre, name, id, author, publ, year, ratign);
        list.append(kniga);
    }
    return list;
}
void storage::deleteBook(int id)
{
    QSqlQuery *q = new QSqlQuery(db);
    q->prepare("delete from Book where id = :id");
    q->bindValue(":id", id);
    q->exec();
}
void storage::deleteBookUser(int id)
{
    QSqlQuery *q = new QSqlQuery(db);
    q->prepare("delete from userInfo where id = :id");
    q->bindValue(":id", id);
    q->exec();
    q->clear();
    q->prepare("delete from users where id = :id");
    q->bindValue(":id", id);
    q->exec();
    q->clear();
}
void storage::regG(QString login, QString name, QString surN, QString status)
{
    QSqlQuery qry(db);
    qry.prepare("insert into userInfo (Name, Surname, Status, id, Card) values(:name, :surname, :status, (select id from users where login = :login), (select id from users where login = :login))");
    qry.bindValue(":login", login);
    qry.bindValue(":name", name);
    qry.bindValue(":surname", surN);
    qry.bindValue(":status", status);
    qry.exec();
}
void storage::regT(QString login)
{QSqlQuery qry(db);
    qry.clear();
    qry.prepare("update users set userInfoId = (select id from users where login =:login) where login = :login");
    qry.bindValue(":login", login);
    qry.exec();
}
QList<book> storage::showAllBook()
{
    adminmenu w;

    QList<book> list;
    int num_rows;
    QSqlQuery * q = new QSqlQuery(db);
    q->prepare("select count(id) as num_rows from  Book");
    q->exec();
    q->first();
    num_rows = q->value(0).toInt();
    w.setRowC(2, num_rows);
    q->prepare("select * from Book");
    q->exec();
    while( q->next() ) {
        int id = q->value(0).toInt();
        QString name = q->value(1).toString();
        QString author = q->value(2).toString();
        QString genre = q->value(3).toString();
        double ratign = q->value(4).toDouble();
        QString publ = q->value(5).toString();
        int year = q->value(6).toInt();
        QString status = q->value(7).toString();
        book kniga(genre, name, id, author, publ, year, ratign);
        list.append(kniga);
    }
    return list;
}


