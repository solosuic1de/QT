#include "adminmenu.h"
#include "ui_adminmenu.h"
#include "darrksufion.h"
#include <string>
#include <QSqlQueryModel>
#include <vector>
#include <QSqlQuery>
#include <addreader.h>
#include <QMessageBox>
#include <orders.h>
#include <QSqlDatabase>
#include <book.h>
#include <QList>
#include <editreader.h>
#include <addbook.h>
#include <QSqlError>
#include <QStackedWidget>
#include <QAbstractButton>
#include <editbook.h>
#include <QDateTime>
#include <QIcon>
#include <QButtonGroup>
#include <loginwindow.h>
adminmenu::adminmenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminmenu)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(darkPalette);
    loadBook();
    loadReaders();
    loadBook();
    loadorders();
    ui->book_2->hideColumn(0);
    ui->book_2->hideColumn(7);
    ui->readers->hideColumn(0);
    ui->readers->selectRow(0);
    ui->orderss->hideColumn(4);
    ui->orderss->hideColumn(5);
    ui->orderss->hideColumn(0);
    // ui->orderss->selectRow(0);
    ui->carby->setVisible(false);
    ui->orby->setVisible(false);

}

adminmenu::~adminmenu()
{
    delete ui;

}

void adminmenu::setLbl()
{
    ui->login->setText(info.login);
    if(info.getRole() == 1)
    {
        ui->role->setText("librarian");
    }
    else
    {
        ui->role->setText("reader");
    }


}



void adminmenu::on_readersBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    loadReaders();
    //@todo
}

void adminmenu::on_bookBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    loadBook();
}



void adminmenu::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    loadorders();
    storage j;
    j.setDb(db);
    QList<orders> ord = j.showAllOrd();
    insertOrders(ord);
}

void adminmenu::on_pushButton_2_clicked()
{
    if(ui->stackedWidget->currentIndex() == 0)
    {
        addBook wind;
        wind.setDb(db);
        wind.exec();
        loadBook();
    }
    else if(ui->stackedWidget->currentIndex() == 1)
    {
        addReader w;
        w.setDb(db);
        w.exec();
        loadReaders();
    }
}

void adminmenu::on_pushButton_4_clicked()
{
    if(ui->stackedWidget->currentIndex() == 0)
    {

        int id = ui->book_2->item(ui->book_2->currentRow(), 0)->text().toInt();
        QString name =  ui->book_2->item(ui->book_2->currentRow(), 1)->text();
        QString author =  ui->book_2->item(ui->book_2->currentRow(), 2)->text();
        QString genre =  ui->book_2->item(ui->book_2->currentRow(), 3)->text();
        double rating =  ui->book_2->item(ui->book_2->currentRow(), 4)->text().toDouble();
        QString publishing =  ui->book_2->item(ui->book_2->currentRow(), 5)->text();
        int year =  ui->book_2->item(ui->book_2->currentRow(), 6)->text().toInt();
        book * Book = new book(genre, name,id,author, publishing, year, rating);
        editBook wind;
        wind.setBook(*Book);
        wind.setLbls();
        wind.setDb(db);
        wind.exec();
        loadBook();
    }
    else  if(ui->stackedWidget->currentIndex() == 1)
    {



        int id = ui->readers->item(ui->readers->currentRow(), 0)->text().toInt();
        QString name =  ui->readers->item(ui->readers->currentRow(), 1)->text();
        QString surname =  ui->readers->item(ui->readers->currentRow(), 2)->text();
        QString status =  ui->readers->item(ui->readers->currentRow(), 4)->text();
        int cardNum =  ui->readers->item(ui->readers->currentRow(), 3)->text().toInt();
        storage j;
        UserInfo user = j.loadUser(name, surname, status, cardNum, id);
        editReader wind;
        wind.setReader(user);
        wind.setLbl();
        wind.exec();
        loadReaders();




    }

}

QString adminmenu::getValuefromT()
{
    QModelIndex currentDiscount  = ui->book_2->currentIndex();
    QString name = ui->book_2->model()->data(ui->book_2->model()->index(currentDiscount.row(),1),0).toString();
    return name;
}

void adminmenu::on_pushButton_3_clicked()
{
    if(ui->stackedWidget->currentIndex() == 0)
    {
        int id = ui->book_2->item(ui->book_2->currentRow(), 0)->text().toInt();
        storage j;
        j.deleteBook(id);
        QList<book> books = j.showAllBook();
        loadBook();
    }
    if(ui->stackedWidget->currentIndex() == 1)
    {
        int id  = ui->readers->item(ui->readers->currentRow(), 0)->text().toInt();
        if(id != info.getCard()){
            storage j;
            j.deleteBookUser(id);

        }
        else
        {
            QMessageBox::critical(this, "Delete user", "You cant delete this account here");
        }
        loadReaders();

    }
}

void adminmenu::on_sortStatus_clicked()
{
    ui->book_2->sortByColumn(8,Qt::AscendingOrder);
}

void adminmenu::on_soerYear_clicked()
{
    ui->book_2->sortByColumn(6,Qt::AscendingOrder);
}

void adminmenu::on_sortAuth_clicked()
{
    ui->book_2->sortByColumn(2,Qt::AscendingOrder);
}

void adminmenu::on_sortGenre_clicked()
{
    ui->book_2->sortByColumn(3,Qt::AscendingOrder);
}

void adminmenu::on_sortName_clicked()
{
    ui->book_2->sortByColumn(1,Qt::AscendingOrder);
}


void adminmenu::on_pushButton_5_clicked()
{

    if(ui->stackedWidget->currentIndex() == 0)
    {
        storage j;
        j.setDb(db);
        QString string =  ui->searchbookLE->text();
        QList<book> books = j.searchBook(string);
        insertBook(books);
    }
}
QString adminmenu::searchT()
{
    return ui->searchbookLE->text();
}


void adminmenu::on_snam_clicked()
{
    ui->readers->sortByColumn(1,Qt::AscendingOrder);
}

void adminmenu::on_scard_clicked()
{
    ui->readers->sortByColumn(3,Qt::AscendingOrder);
}

void adminmenu::on_sstats_clicked()
{
    ui->readers->sortByColumn(4,Qt::AscendingOrder);
}

void adminmenu::on_accept_clicked()
{
    if(ui->orderss->item(ui->orderss->currentRow(), 0))
    {
        int id = ui->orderss->item(ui->orderss->currentRow(), 0)->text().toInt();
        QString status =  ui->orderss->item(ui->orderss->currentRow(), 3)->text();
        storage j;
        j.Accepted(id, status);
        QList<orders> ord = j.showAllOrd();
        insertOrders(ord);

    }}

void adminmenu::on_close_clicked()
{
    if(ui->orderss->item(ui->orderss->currentRow(), 0)){
        int id = ui->orderss->item(ui->orderss->currentRow(), 5)->text().toInt();
        int idr = ui->orderss->item(ui->orderss->currentRow(), 0)->text().toInt();
        qDebug()<<id;
        QString status =  ui->orderss->item(ui->orderss->currentRow(), 3)->text();
        qDebug()<<status;
        storage j;
        j.setDb(db);
        j.CloseOrder(id, status, idr);
        QList<orders> ord = j.showAllOrd();
        insertOrders(ord);

    }
}

void adminmenu::on_decline_clicked()
{
    if(ui->orderss->item(ui->orderss->currentRow(), 0)){
        storage j;
        int id = ui->orderss->item(ui->orderss->currentRow(), 0)->text().toInt();

        QString status =  ui->orderss->item(ui->orderss->currentRow(), 3)->text();

        j.DeclineOrder(id, status);
        j.setDb(db);
        QList<orders> list = j.showActiveOrd();
        insertOrders(list);
    }
}
void adminmenu::loadReaders()
{
    int num_rows,c,r;

    QSqlQuery * q = new QSqlQuery(db);

    q->exec("select count(id) as num_rows from userInfo"); //QMessageBox::critical(this, "Database", q->lastError().text());
    q->first();
    num_rows = q->value(0).toInt();
    ui->readers->setRowCount(num_rows);
    if(!q->exec("select * from userInfo")) QMessageBox::critical(this, "Database", q->lastError().text());
    for(r = 0, q->first(); q->isValid(); q->next(), ++r)
    {
        for(c = 0; c < 5; ++c)
        {
            ui->readers->horizontalHeader()->sortIndicatorOrder();
            ui->readers->setItem(r,c,new QTableWidgetItem(q->value(c).toString()));
        }
    }
}
int adminmenu::getSelectedOrd()
{

    return ui->orderss->item(ui->orderss->currentRow(), 0)->text().toInt();

}
bool adminmenu::isSelected()
{
    return ui->orderss->item(ui->orderss->currentRow(), 0);
}
QString adminmenu::getSelectedStatus()
{
    QString status =  ui->orderss->item(ui->orderss->currentRow(), 3)->text();
    return status;
}

void adminmenu::on_book_2_itemClicked(QTableWidgetItem *item)
{
    int id = ui->book_2->item(ui->book_2->currentRow(), 0)->text().toInt();
    storage j;
    QByteArray pic = j.bookPic(id);
    QPixmap img;
    img.loadFromData(pic, "PNG");
    ui->picBook->setPixmap(img);
}

void adminmenu::on_orderss_itemClicked(QTableWidgetItem *item)
{
    int id = ui->orderss->item(ui->orderss->currentRow(), 0)->text().toInt();
    storage j;
    j.setDb(db);
    int ind = j.getBookIdfromOrd(id);
    qDebug()<<ind;
    QString name = j.getBookName(id);
    ui->NameL->setText(name);
    QByteArray pic = j.bookPic(ind);
    // qDebug()<<pic;
    QPixmap img;
    img.loadFromData(pic, "PNG");
    ui->pic->setPixmap(img);
    //    q->clear();
    QList<QString> list = j.getOrdN(id);

    //    q->prepare("select * from userInfo where id =(select userId from Orders where id =:id)");
    //    q->bindValue(":id", id);
    //    q->exec();
    //    q->first();
    ui->nameo->setText(j.getN(id));
    ui->surneo->setText(list.at(1));
    ui->curdeo->setText(list.at(2));
    ui->carby->setVisible(true);
    ui->orby->setVisible(true);

}

void adminmenu::on_pushButton_6_clicked()
{
    storage j;
    QList<orders> ord = j.showActiveOrd();
    insertOrders(ord);

}
void adminmenu::loadBook()
{

    int num_rows,c,r;

    QSqlQuery * q = new QSqlQuery(db);

    q->exec("select count(id) as num_rows from Book");
    q->first();
    num_rows = q->value(0).toInt();
    ui->book_2->setRowCount(num_rows);
    q->exec("select * from Book");
    for(r = 0, q->first(); q->isValid(); q->next(), ++r)
    {
        for(c = 0; c < 9; ++c)
        {
            ui->book_2->horizontalHeader()->sortIndicatorOrder();
            ui->book_2->setItem(r,c,new QTableWidgetItem(q->value(c).toString()));
        }
    }

}
void adminmenu::setRowC(int id, int num_rows)
{

    if(id == 1)
    {
        ui->orderss->setRowCount(num_rows);
    }
    if(id == 2)
    {
        ui->book_2->setRowCount(num_rows);
    }

}
void adminmenu::insertOrders(QList <orders> ord)
{
    if(ui->orderss->rowCount()>0)
        ui->orderss->clearContents();
    for(int i = 0; i < ord.count(); ++i)
    {
        orders ok = ord.at(i);
        QString id = QString::fromStdString(std::to_string(ord.at(i).id));
        QString start = ok.getStart();
        QString end = ok.getEnd();
        QString status = ord.at(i).status;
        QString userId = QString::fromStdString(std::to_string(ord.at(i).userId));
        QString bookId = QString::fromStdString(std::to_string(ord.at(i).bookId));
        ui->orderss->horizontalHeader()->sortIndicatorOrder();
        ui->orderss->setItem(i,0,new QTableWidgetItem(id));
        ui->orderss->horizontalHeader()->sortIndicatorOrder();
        ui->orderss->setItem(i,1,new QTableWidgetItem(start));
        ui->orderss->horizontalHeader()->sortIndicatorOrder();
        ui->orderss->setItem(i,2,new QTableWidgetItem(end));
        ui->orderss->horizontalHeader()->sortIndicatorOrder();
        ui->orderss->setItem(i,3,new QTableWidgetItem(status));
        ui->orderss->horizontalHeader()->sortIndicatorOrder();
        ui->orderss->setItem(i,4,new QTableWidgetItem(bookId));
        ui->orderss->horizontalHeader()->sortIndicatorOrder();
        ui->orderss->setItem(i,5,new QTableWidgetItem(userId));
    }}



void adminmenu::insertBook(QList <book> books)
{
    ui->book_2->clearContents();
    for(int i = 0; i < books.count(); ++i)
    {
        book ok = books.at(i);
        QString id = QString::fromStdString(std::to_string(ok.getId()));
        QString name = ok.getName();
        QString author = ok.getAutor();
        QString genre = ok.getGenre();
        QString rating = QString::fromStdString(std::to_string(ok.getRating()));
        QString publisher = ok.getPublishing();
        QString year = QString::fromStdString(std::to_string(ok.getYear()));
        QString status = ok.getStatus();
        ui->book_2->horizontalHeader()->sortIndicatorOrder();
        ui->book_2->setItem(i,0,new QTableWidgetItem(id));
        ui->book_2->horizontalHeader()->sortIndicatorOrder();
        ui->book_2->setItem(i,1,new QTableWidgetItem(name));
        ui->book_2->horizontalHeader()->sortIndicatorOrder();
        ui->book_2->setItem(i,2,new QTableWidgetItem(author));
        ui->book_2->horizontalHeader()->sortIndicatorOrder();
        ui->book_2->setItem(i,3,new QTableWidgetItem(genre));
        ui->book_2->horizontalHeader()->sortIndicatorOrder();
        ui->book_2->setItem(i,4,new QTableWidgetItem(rating));
        ui->book_2->horizontalHeader()->sortIndicatorOrder();
        ui->book_2->setItem(i,5,new QTableWidgetItem(publisher));
        ui->book_2->horizontalHeader()->sortIndicatorOrder();
        ui->book_2->setItem(i,6,new QTableWidgetItem(year));
        ui->book_2->horizontalHeader()->sortIndicatorOrder();
        ui->book_2->setItem(i,7,new QTableWidgetItem(" "));
        ui->book_2->horizontalHeader()->sortIndicatorOrder();
        ui->book_2->setItem(i,8,new QTableWidgetItem(status));
    }
}
void adminmenu::loadorders()
{
    int num_rows,c,r;

    QSqlQuery * q = new QSqlQuery(db);

    q->exec("select count(id) as num_rows from Orders");
    q->first();
    num_rows = q->value(0).toInt();
    ui->orderss->setRowCount(num_rows);
    q->exec("select * from Orders");
    for(r = 0, q->first(); q->isValid(); q->next(), ++r)
    {
        for(c = 0; c < 6; ++c)
        {
            ui->orderss->horizontalHeader()->sortIndicatorOrder();
            ui->orderss->setItem(r,c,new QTableWidgetItem(q->value(c).toString()));
        }
    }
}
