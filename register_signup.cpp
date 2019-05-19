#include "ui_register_signup.h"
#include "loginwindow.h"
#include <QSql>
#include <QSqlDatabase>
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <storage.h>
#include <QDialog>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QApplication>
#include <loginwindow.h>
#include <QSqlError>
#include <QDebug>
#include <register_signup.h>
#include <mainwindow.h>
#include <QString>
#include "adminmenu.h"
#include<QPushButton>


register_signUp::register_signUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::register_signUp)
{
    ui->setupUi(this);
    QPushButton *okBtn = ui->buttonBox->button(QDialogButtonBox::Ok);
    okBtn->setDisabled(true);
    ui->checkBox->setChecked(false);
    // w.conn();
    QPalette darkPalette;
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
}



register_signUp::~register_signUp()
{
    delete ui;
}
regData register_signUp::registerData()
{
    regData data;
    data.login = ui->loginLE_2->text();

    data.password2 = QString("%1").arg(QString(QCryptographicHash::hash(ui->password2LE->text().toUtf8(),QCryptographicHash::Md5).toHex()));
    data.password = QString("%1").arg(QString(QCryptographicHash::hash(ui->passwordLE_2->text().toUtf8(),QCryptographicHash::Md5).toHex()));

    data.role = 0;



    return data;
}
void register_signUp::validAdd()
{
    if (!ui->loginLE_2->text().isEmpty()&&!ui->password2LE->text().isEmpty()&&!ui->passwordLE_2->text().isEmpty()&&!ui->namel->text().isEmpty()&&!ui->surnamel->text().isEmpty())
    {
        if(ui->passwordLE_2->text() == ui->password2LE->text())
        {
            qDebug()<<"jiu";
            QPushButton *okBtn = ui->buttonBox->button(QDialogButtonBox::Ok);
            okBtn->setEnabled(true);

        }
        else
        {
            QPushButton *okBtn = ui->buttonBox->button(QDialogButtonBox::Ok);
            okBtn->setDisabled(true);
        }
    }
}
void  register_signUp::addUser (QString & login, QString & password, QString & password2, int role)
{
    storage j;
    QString name = ui->namel->text();
    QString surN = ui->surnamel->text();
    QString status = "Not debtor";
    QSqlQuery qry;
    qry.prepare("insert into users (login, password_hash) values ('"+login+"','"+password+"')");
    qry.exec();
    qry.clear();
    j.regG(login, name, surN, status);
    j.regT(login);



}

void register_signUp::on_loginLE_2_textChanged(const QString &arg1)
{
    validAdd();
}

void register_signUp::on_passwordLE_2_textChanged(const QString &arg1)
{
    validAdd();
}

void register_signUp::on_password2LE_textChanged(const QString &arg1)
{
    validAdd();
}



void register_signUp::on_checkBox_stateChanged(int arg1)
{
    QPushButton *okBtn = ui->buttonBox->button(QDialogButtonBox::Ok);
    if(okBtn->isEnabled())
    {
        if(!ui->checkBox->isChecked())
            okBtn->setDisabled(true);
    }
    else
    {
        if (!ui->loginLE_2->text().isEmpty()&&!ui->password2LE->text().isEmpty()&&!ui->passwordLE_2->text().isEmpty() &&!ui->namel->text().isEmpty()&&!ui->surnamel->text().isEmpty())
        {
            if(ui->checkBox->isChecked())
                okBtn->setEnabled(true);
        }
    }
}

void register_signUp::on_buttonBox_accepted()
{
    regData dataReg =registerData();
    addUser(dataReg.login, dataReg.password, dataReg.password2, 0);
}
