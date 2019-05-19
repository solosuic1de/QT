#ifndef EDITBOOK_H
#define EDITBOOK_H

#include <QDialog>
#include <QSqlDatabase>
#include <adminmenu.h>
#include <book.h>

namespace Ui {
class editBook;
}

class editBook : public QDialog
{
    Q_OBJECT

public:

    void setDb(QSqlDatabase db)
    {
        this->db = db;
    }
    void setBook(book Book)
    {
        this->Book = Book;
    }
    explicit editBook(QWidget *parent = 0);
    void setLbls();
    ~editBook();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::editBook *ui;
    QSqlDatabase db;
    //int ind;
    book Book;
    //adminmenu window;
};

#endif // EDITBOOK_H
