#include "editbook.h"
#include "ui_editbook.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <adminmenu.h>

editBook::editBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editBook)
{
    ui->setupUi(this);

}

editBook::~editBook()
{
    delete ui;
}

void editBook::setLbls()
{

    ui->setupUi(this);
    ui->edbName->setText(Book.getName());
    ui->edAut->setText(Book.getAutor());
    ui->edPublB->setText(Book.getPublishing());
    ui->edRating->setValue(Book.getRating());
    ui->edYear->setValue(Book.getYear());
    ui->genre->setCurrentText(Book.getGenre());
}
void editBook::on_buttonBox_accepted()
{
    int id = Book.getId();
    QString name = ui->edbName->text();
    QString author = ui->edAut->text();
    QString genre = ui->genre->currentText();
    QString publisher = ui->edPublB->text();
    QString status = ui->comboBox->currentText();
    int year = ui->edYear->value();
    int rating = ui->edRating->value();
    storage j;
    j.setDb(db);
    j.edit(name,author,publisher,genre,rating,year,id,status);

}
