#include "addbook.h"
#include "ui_addbook.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QByteArray>
#include <QSqlError>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>
#include <QApplication>
addBook::addBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addBook)
{
    ui->setupUi(this);



}

addBook::~addBook()
{
    delete ui;
}

void addBook::on_buttonBox_accepted()
{

    QString name = ui->bname->text();
    QString author = ui->bauthor->text();
    QString genre = ui->genre->currentText();
    QString publisher = ui->bpublisher->text();
    int year = ui->byear->value();
    int rating = ui->brating->value();
    QSqlQuery q;
    QString status = "Available";
    q.prepare("insert into Book (name,author,genre,rating,publisher,year,status, pic) values(:name,:author,:genre,:rating,:publisher,:year,:status,:pic)");
    q.bindValue(":name", name);
    q.bindValue(":author", author);
    q.bindValue(":genre", genre);
    q.bindValue(":rating", rating);
    q.bindValue(":publisher", publisher);
    q.bindValue(":year", year);
    q.bindValue(":pic", this->arr);
    q.bindValue(":status", status);
    if(q.exec())
    {
        QMessageBox::information(this, "lib3000", name +" successfuly added");
    }
    else
    {
        QMessageBox::critical(this, "Adding book", q.lastError().text());
    }


}

void addBook::on_photos_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"),
                                                    "/home",
                                                    ("PNG (*.png)"));
    QPixmap avatar(fileName);
    avatar = avatar.scaled(200,300);
    QByteArray arr;
    QBuffer buff(&arr);
    buff.open(QIODevice::WriteOnly);
    avatar.save(&buff,"PNG");
    this->arr = arr;




}
