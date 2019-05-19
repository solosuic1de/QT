#include "editreader.h"
#include "ui_editreader.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <storage.h>

editReader::editReader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editReader)
{
    ui->setupUi(this);
}

editReader::~editReader()
{
    delete ui;
}
void editReader::setLbl()
{
    ui->edName->setText(info.getName());
    ui->edSurn->setText(info.getSurnM());
    if(info.getRole() == 1) ui->edRole->setCurrentText("librarian");
    else ui->edRole->setCurrentText("Reader");
    ui->edStatus->setCurrentText(info.getStatus());
}

void editReader::on_buttonBox_accepted()
{
    int role;
    QString name = ui->edName->text();
    QString surN = ui->edSurn->text();
    QString status = ui->edStatus->currentText();
    if(ui->edRole->currentText() == "librarian") role = 1;
    else role = 0;
    storage j;
    int id = info.getCard();
    j.editUsers(name, surN, id, status);
    j.updrole(id, role);
    //    QSqlQuery * q = new QSqlQuery(db);
    //    q->prepare("update users set role = :role where id=:id");
    //    q->bindValue(":role" , role);
    //    q->bindValue(":id" , info.getCard());

}
