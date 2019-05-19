#ifndef STORAGE_H
#define STORAGE_H
#include <QSql>
#include <QSqlDatabase>
#include <QList>
#include <orders.h>
#include <QSqlQuery>
#include <adminmenu.h>
#include <userinfo.h>
#include <QSqlError>
class storage
{
public:
    QList<orders> showAllOrd();
    // void showSelecOrd();
    QList<orders> showActiveOrd();
    QList<orders> DeclineOrder(int id, QString status);
    storage();
    QList<book> showAllBook();
    void updrole(int id, int role);
    QByteArray bookPic(int id);
    void deleteBook(int id);
    QString getBookName(int id);
    QList <QString> getOrdN(int id);
    void edit(QString name, QString author, QString publisher, QString genre, double rating, int year, int id, QString status);
    void editUsers(QString name, QString surN, int id, QString status);
    int getBookIdfromOrd(int id);
    UserInfo loadUser(QString name, QString surname, QString status, int cardNum, int id);
    void deleteBookUser(int id);
    void regT(QString login);
    QString getN(int id);
    void regG(QString login, QString name, QString surN, QString status);
    void addReader(QString login, QString password, QString name, QString surN, QString status);
    void cinform(int card, QString name, QString surn, QString status);
    QList<orders> showOrders(int id);
    void orderBtn(QString status, QString start, QString end, int id, QString name, QString author, QString genre, double rating, QString publisher, int year, int userID);
    void setDb(QSqlDatabase db)

    {
        this->db = db;
    }
    void CloseOrder(int id, QString status, int ordid);
    void Accepted(int id, QString status);
    QList<book> searchBook(QString string);
private:
    QSqlDatabase db;



};

#endif // STORAGE_H
