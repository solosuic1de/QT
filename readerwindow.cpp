#include "readerwindow.h"
#include "ui_readerwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <iostream>
#include <QPixelFormat>
#include <QPixmap>
#include <QByteArray>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
using namespace std;
readerwindow::readerwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::readerwindow)
{
    ui->setupUi(this);
    ui->book->hideColumn(0);
    ui->book->hideColumn(7);
    ui->book->hideColumn(8);
    ui->erdered->hideColumn(0);
    ui->erdered->hideColumn(7);
    ui->erdered->hideColumn(8);
    ui->stackedWidget->setCurrentIndex(0);
    qDebug()<<info.getCard();
}

readerwindow::~readerwindow()
{
    delete ui;
}

void readerwindow::on_scifi_2_clicked()
{

    setId(1);
    QString q = "Sci-fiction";
    loadIn(q);


}


void readerwindow::on_Romance_2_clicked()
{
    setId(2);
    QString q = "Romance";
    loadIn(q);
}

void readerwindow::on_Horror_2_clicked()
{
    setId(3);
    QString q = "Horror";
    loadIn(q);
}

void readerwindow::on_Thriller_2_clicked()
{
    setId(4);
    QString q = "Thriller";
    loadIn(q);

}

void readerwindow::on_History_2_clicked()
{
    setId(5);
    QString q = "History";
    loadIn(q);
}

void readerwindow::loadIn(QString & string)
{
    int num_rows,c,r;
    QSqlQuery * q = new QSqlQuery(db);
    q->prepare("select count(id) as num_rows from Book where genre =:genre and status =:status");

    q->bindValue(":genre", string);
    q->bindValue(":status", "Available");
    q->exec();
    q->first();
    num_rows = q->value(0).toInt();
    ui->book->setRowCount(num_rows);
    q->prepare("select * from Book where genre =:genre and status =:status");
    q->bindValue(":genre", string);
    q->bindValue(":status", "Available");

    if(!q->exec())  QMessageBox::critical(this, "Database", q->lastError().text());
    for(r = 0, q->first(); q->isValid(); q->next(), ++r)
    {
        for(c = 0; c < 9; ++c)
        {
            ui->book->horizontalHeader()->sortIndicatorOrder();
            ui->book->setItem(r,c,new QTableWidgetItem(q->value(c).toString()));
        }
    }
}

void readerwindow::on_clildb_2_clicked()
{
    setId(6);
    QString q = "Children`s book";
    loadIn(q);
}

void readerwindow::on_Fantasy_2_clicked()
{
    setId(7);
    QString q = "Fantasy";
    loadIn(q);
}

void readerwindow::on_Fiction_2_clicked()
{
    setId(8);
    QString q = "Ficion";
    loadIn(q);
}

void readerwindow::on_orderbtn_clicked()
{
    QString name =  ui->book->item(ui->book->currentRow(), 1)->text();
    QString author =  ui->book->item(ui->book->currentRow(), 2)->text();
    QString genre =  ui->book->item(ui->book->currentRow(), 3)->text();
    double rating =  ui->book->item(ui->book->currentRow(), 4)->text().toDouble();
    QString publisher =  ui->book->item(ui->book->currentRow(), 5)->text();
    int year =  ui->book->item(ui->book->currentRow(), 6)->text().toInt();
    int id = ui->book->item(ui->book->currentRow(), 0)->text().toInt();
    QString start = QDateTime::currentDateTime().toString(Qt::ISODate);
    QString status = "waiting";
    QString act = "waiting";
    QString end = "-";
    storage j;
    j.orderBtn(status, start, end, id, name, author, genre, rating, publisher, year, info.getCard());
    QString genr;
    if(idx == 1)
    {
        genr = "Sci-fiction";
    }
    else if (idx == 2)
    {
        genr = "Romance";
    }
    else if (idx == 3)
    {
        genr = "Horror";
    }
    else if (idx == 4)
    {
        genr = "Thriller";
    }
    else if (idx == 5)
    {
        genr = "History";
    }
    else if (idx == 6)
    {
        genr = "Children`s book";
    }
    else if (idx == 7)
    {
        genr = "Fantasy";
    }
    else if (idx == 8)
    {
        genr = "Ficion";
    }
    loadIn(genr);

}

void readerwindow::on_cabinet_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    loadOrd();

}

void readerwindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void readerwindow::setRowCount(int id)
{
    ui->erdered->setRowCount(id);
}
void readerwindow::loadOrd(){
    int num_rows,c,r;
    storage j;
    QList<orders> list = j.showOrders(info.getCard());
    qDebug()<<list.count();
    QSqlQuery * q = new QSqlQuery(db);
    q->prepare("select count(id) as num_rows from Orders where userId =:id");
    q->bindValue(":id", info.getCard());
    if(!q->exec()) QMessageBox::critical(this, "Database", q->lastError().text());
    q->first();
    num_rows = q->value(0).toInt();
    ui->erdered->setRowCount(num_rows);
    q->prepare("select * from Orders where userId = :id");
    q->bindValue(":id", info.getCard());
    if(!q->exec()) QMessageBox::critical(this, "Database", q->lastError().text());
    for(r = 0, q->first(); q->isValid(); q->next(), ++r)
    {
        for(c = 0; c < 6; ++c)
        {
            ui->erdered->horizontalHeader()->sortIndicatorOrder();
            ui->erdered->setItem(r,c,new QTableWidgetItem(q->value(c).toString()));
        }
    }
}

void readerwindow::on_cinform_clicked()
{
    storage j;
    QString name = ui->NameLE->text();
    QString surn = ui->surn->text();
    int card = info.getCard();
    QString status = info.getStatus();
    j.setDb(db);
    j.cinform(card, name, surn, status);



}
void readerwindow::setName()
{
    ui->NameLE->setText(info.getName());
    ui->surn->setText(info.getSurnM());
}

void readerwindow::on_book_itemClicked(QTableWidgetItem *item)
{
    int id = ui->book->item(ui->book->currentRow(), 0)->text().toInt();
    QSqlQuery * q =  new QSqlQuery(db);
    q->prepare("select * from Book where id =:id");
    q->bindValue(":id", id);
    q->exec();
    q->first();
    QByteArray pic = q->value(7).toByteArray();
    QPixmap img;
    img.loadFromData(pic, "PNG");
    ui->piclbl->setPixmap(img);
    ui->namel->setText(q->value(1).toString());
    ui->autl->setText(q->value(2).toString());
    ui->genrel->setText(q->value(3).toString());
    ui->ratl->setText(q->value(4).toString());
    ui->publ->setText(q->value(5).toString());
    ui->yearl->setText(q->value(6).toString());

}
void readerwindow::setLogin()
{
    ui->loginl->setText(info.getLogin());
}
void readerwindow::on_erdered_itemClicked(QTableWidgetItem *item)
{
    int id = ui->erdered->item(ui->erdered->currentRow(), 0)->text().toInt();
    QSqlQuery * q =  new QSqlQuery(db);
    q->prepare("select * from Book where id =(select bookId from Orders where id =:id)");
    q->bindValue(":id", id);
    q->exec();
    q->first();
    ui->nameL->setText(q->value(1).toString());
    ui->autL->setText(q->value(2).toString());
    QByteArray pic = q->value(7).toByteArray();
    QPixmap img;
    img.loadFromData(pic, "PNG");
    ui->pic1->setPixmap(img);



}

