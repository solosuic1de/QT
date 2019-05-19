#ifndef EDITREADER_H
#define EDITREADER_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <userinfo.h>
namespace Ui {
class editReader;
}

class editReader : public QDialog
{
    Q_OBJECT

public:
    void setReader(UserInfo info)
    {
        this->info = info;
    }
    void setLbl();
    explicit editReader(QWidget *parent = 0);
    ~editReader();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::editReader *ui;
    UserInfo info;
    QSqlDatabase db;

};

#endif // EDITREADER_H
