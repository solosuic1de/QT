#ifndef ORDERS_H
#define ORDERS_H
#include <QDateTime>

class orders
{
public:
    orders(int id, QString start, QString endl, QString status, int bookId, int userId);
    int id;
    QDateTime start;
    QDateTime end;
    QString status;
    int bookId;
    int userId;
    QString getStart()
    {
        return  this->start.toString(Qt::ISODate);
    }
    QString getEnd()
    {
        return this->end.toString(Qt::ISODate);
    }

};

#endif // ORDERS_H
