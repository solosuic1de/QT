#ifndef REGISTER_SIGNUP_H
#define REGISTER_SIGNUP_H
#include <QSqlDatabase>
#include <QDialog>
#include <loginwindow.h>
#include <QString>
#include <user.h>
struct regData
{
    QString login;
    QString password;
    QString password2;
    int role;
};
namespace Ui {
class register_signUp;
}

class register_signUp : public QDialog
{
    Q_OBJECT

public:
    void setDb(QSqlDatabase db)
    {
        this->db = db;
    }
    explicit register_signUp(QWidget *parent = 0);
    ~register_signUp();
    regData registerData();
    void addUser(  QString & login, QString & password, QString & password2, int role);

private slots:
    void on_loginLE_2_textChanged(const QString &arg1);

    void on_passwordLE_2_textChanged(const QString &arg1);

    void on_password2LE_textChanged(const QString &arg1);
    void validAdd();


    void on_checkBox_stateChanged(int arg1);

    void on_buttonBox_accepted();

private:
    Ui::register_signUp *ui;
//       QSqlDatabase database;
          loginWindow w;
          QSqlDatabase db;
};

#endif // REGISTER_SIGNUP_H
