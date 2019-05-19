#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QDialog>
#include <loginwindow.h>
#include <QSqlDatabase>

namespace Ui {
class addBook;
}

class addBook : public QDialog
{
    Q_OBJECT

public:
    void setDb(QSqlDatabase db)
    {
        this->db = db;
    }
      loginWindow con;
    explicit addBook(QWidget *parent = 0);
    ~addBook();

private slots:
    void on_buttonBox_accepted();

    void on_photos_clicked();

private:
    Ui::addBook *ui;
    QSqlDatabase db;
    loginWindow wind;
    QByteArray arr;

};

#endif // ADDBOOK_H
