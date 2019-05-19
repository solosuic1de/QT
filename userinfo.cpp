#include "userinfo.h"

UserInfo::UserInfo(int cardNum, QString name, QString surName, QString status, QString login, int role)
{
    this->cardNum = cardNum;
    this->name = name;
    this->surName = surName;
    this->status = status;
    this->login = login;

    this->role = role;
}

