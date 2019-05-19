#include "loginwindow.h"
#include <QSql>
#include <QSqlDatabase>
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QDialog>
#include <vector>
#include <QSqlQuery>
#include <userinfo.h>
#include <QSqlError>
#include <QDebug>
#include <register_signup.h>
#include <QCryptographicHash>
#include <mainwindow.h>
#include <iostream>
#include <QString>
#include "adminmenu.h"
#include <readerwindow.h>
#include<QPushButton>
using namespace std;
loginWindow::loginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);
    QPushButton *okBtn = ui->login;
    okBtn->setDisabled(true);
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

loginWindow::~loginWindow()
{
    delete ui;
}


void loginWindow::on_LLoginLE_textChanged(const QString &arg1)
{
    validAdd();
}

void loginWindow::on_LpassLE_textChanged(const QString &arg1)
{
    validAdd();
}
void loginWindow::validAdd()
{
    if (!ui->LLoginLE->text().isEmpty()&&!ui->LpassLE->text().isEmpty())
    {
        QPushButton *okBtn = ui->login;
        okBtn->setEnabled(true);

    }
    else
    {
        QPushButton *okBtn = ui->login;
        okBtn->setDisabled(true);
    }
}

void loginWindow::on_login_clicked()
{
    QString login, pass;
    pass =  QString("%1").arg(QString(QCryptographicHash::hash(ui->LpassLE->text().toUtf8(),QCryptographicHash::Md5).toHex()));
    login = ui->LLoginLE->text();
    qDebug()<<login + " " + pass;
    QSqlQuery qry;
    qry.prepare("SELECT * FROM users WHERE login = :login AND password_hash = :password");
    qry.bindValue(":login", login);
    qry.bindValue(":password", pass);
    if(qry.exec());
    {
        int count = 0;
        while(qry.next())
        {
            count++;
        }
        if(count==1)
        {
            ui->label->setText("correct");
            this->hide();

            qry.clear();
            qry.prepare("SELECT role FROM users WHERE login = :login AND password_hash = :password");
            qry.bindValue(":login", login);
            qry.bindValue(":password", pass);
            qry.exec();
            qry.first();
            int role = qry.value(0).toInt();
            qry.clear();
            qry.prepare("SELECT * FROM userInfo WHERE id = (SELECT id FROM users WHERE login  = :login)");
            qry.bindValue(":login", login);
            qry.exec();
            qry.first();
            QString name = qry.value(1).toString();
            QString surname = qry.value(2).toString();
            int card = qry.value(3).toInt();
            QString statuis = qry.value(4).toString();
            UserInfo * info = new UserInfo(card, name, surname, statuis, login, role);
            if(role == 1)
            {
                adminmenu w;
                w.setUserInfo(*info);
                w.setLbl();
                w.setDb(db);
                w.setModal(true);
                w.exec();
            }
            else
            {
                readerwindow w;
                w.setUserInfo(*info);
                w.setName();
                w.setLogin();
                w.setDb(db);
                w.setModal(true);
                w.exec();
            }

        }
        if(count>1)
        {
            ui->label->setText("Duplicate login and password");
        }
        if(count<1)
        {
            ui->label->setText("Login or password isn`t correct");
        }
    }



}

void loginWindow::on_singB_clicked()
{
    register_signUp w;
    w.setDb(db);
    w.setModal(true);
    w.exec();
}
