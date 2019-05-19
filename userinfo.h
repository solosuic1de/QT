#ifndef USERINFO_H
#define USERINFO_H
#include <QString>
#include <QSqlDatabase>
class UserInfo
{
public:
    UserInfo(){}
    UserInfo(int cardNum, QString name, QString surName, QString status, QString login, int role);
    int cardNum;
    QString name;
    QString login;
    int role;
    QString surName;
    QString status;

    QString getName(){
        return this->name;
    }
    QString getLogin(){
        return this->login;
    }

    QString getSurnM(){
        return this->surName;
    }
    QString getStatus(){
        return this->status;
    }
    int getCard(){
        return this->cardNum;
    }
    int getRole()
    {
        return this->role;
    }




};

#endif // USERINFO_H
