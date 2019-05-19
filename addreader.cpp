#include "addreader.h"
#include "ui_addreader.h"
#include <QCryptographicHash>
#include <QSqlQuery>
#include <QMessageBox>
#include <storage.h>
#include <QSqlError>

addReader::addReader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addReader)
{
    ui->setupUi(this);
}

addReader::~addReader()
{
    delete ui;
}

void addReader::on_buttonBox_accepted()
{
    storage j;
    QString name = ui->edName->text();
    QString status = "Not debtor";
    QString surN = ui->edSurn->text();
    QString login = ui->loginLE->text();
    QString password = QString("%1").arg(QString(QCryptographicHash::hash(ui->password->text().toUtf8(),QCryptographicHash::Md5).toHex()));
    j.addReader(login, password, name, surN, status);
}
