#include "user.h"

User::User(QString)
void User::setLogin(QString & login)
{
    this->login = login;
}
void User::setPass(QString & pass)
{
    this->password = pass;
}
void User::setRole(int role)
{
    this->role = role;
}
void User::setId(int id){
    this->id = id;
}
int User::getId()
{
    return this->id;
}
int User::getRole()
{
    return this->role;
}
QString User::getLogin()
{
    return this->login;
}
QString User::getPassword_hash()
{
    return this->password;
}
