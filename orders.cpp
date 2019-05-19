#include "orders.h"

orders::orders(int id, QString start, QString endl, QString status, int bookId, int userId)
{
    this->id = id;
    QDateTime st = QDateTime::fromString(start, Qt::ISODate);
    QDateTime en = QDateTime::fromString(endl, Qt::ISODate);
    this->start = st;
    this->end = en;
    this->bookId = bookId;
    this->userId = userId;
    this->status = status;
}
