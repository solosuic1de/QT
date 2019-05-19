#ifndef BOOK_H
#define BOOK_H
#include <QString>
#include <iostream>

class book
{
    QString name;
    QString autor;
    //QString comment;
    QString publishing;
    //int readers;
    QString status;
    QString genre;
    int year;
    int id;
    double rating;

public:
    book(QString genre, QString & name, int id, QString &autor, /*QString &comment,*/ QString& publishing, /*int readers,*/ int year, double rating);
    book(){}
    QString getName();
    QString getAutor();
    QString getGenre();
 //   QString getComment();
    int getId();
    QString getPublishing();
//    int getReaders();
    int getYear();
    double getRating();
    QString getStatus();
    void setName(QString & name);
    void setAutor(QString & autor);
  //  void setComment(QString &comment);
    void setPublishing(QString &publishing);
//    void setReaders(int readers);
    void setYear(int year);
    void setRating(double rating);
    void setStatus(QString status);


};

#endif // BOOK_H
