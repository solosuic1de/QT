#ifndef USER_H
#define USER_H
#include <QString>
#include <QObject>


class User
{
    int id;
    QString login;
    QString password;
    int role;

    Q_OBJECT
public:

    void setLogin(QString & login);
    void setPass(QString & pass);
    void setRole(int role);
    void setId(int id);
    int getId();
    int getRole();
    QString getLogin();
    QString getPassword_hash();




signals:

public slots:
};

#endif // USER_H
