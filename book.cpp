#include "book.h"

book:: book(QString genre, QString & name, int id, QString &autor, /*QString &comment,*/ QString& publishing, /*int readers,*/ int year, double rating)
{
    this->genre = genre;
    this->name=name;
    this->autor = autor;
    this->id = id;
    QString status = "Available";
    this->status = status;
    this->publishing = publishing;
    this-> year = year;
    this->rating = rating;
}
QString book::getName()
{
    return this->name;
}
QString book::getAutor()
{
    return this->autor;
}

QString book::getPublishing()
{
    return this->publishing;
}

int book:: getYear()
{
    return this->year;
}
double book::getRating()
{
    return this->rating;
}
QString book::getStatus()
{
    return this->status;
}
void book::setName(QString& name)
{
    this->name = name;
}
void book::setAutor(QString& autor)
{
    this->autor = autor;
}

void book::setPublishing(QString& publishing)
{
    this->publishing = publishing;
}

void book::setYear(int year)
{
    this->year = year;
}
void book::setRating(double rating)
{
    this->rating = rating;
}
void book::setStatus(QString status)
{
    this->status = status;
}
QString book::getGenre()
{
    return this->genre;
}
int book::getId()
{
    return this->id;
}
