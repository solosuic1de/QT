#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <register_signup.h>
#include <QMessageBox>
#include <QSqlError>
#include <loginwindow.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

}

MainWindow::~MainWindow()
{

    delete ui;
}




