#ifndef READERWINDOW_H
#define READERWINDOW_H

#include <QDialog>
#include <QSqlDatabase>
#include <userinfo.h>
#include <QTableWidgetItem>
#include <storage.h>

namespace Ui {
class readerwindow;
}

class readerwindow : public QDialog
{
    Q_OBJECT

public:
    void setDb(QSqlDatabase db)
    {
        this->db = db;
    }
    void setUserInfo(UserInfo info)
    {
        this->info = info;
    }
    ;
    explicit readerwindow(QWidget *parent = 0);
    ~readerwindow();
    void setId(int idx)
    {
        this->idx = idx;
    }
    void setLogin();

 void setRowCount(int id);

    void setName();
private slots:
    void on_scifi_2_clicked();
    void loadIn(QString & string);
    void loadOrd();
    void on_Romance_2_clicked();

    void on_Horror_2_clicked();

    void on_Thriller_2_clicked();

    void on_History_2_clicked();

    void on_clildb_2_clicked();

    void on_Fantasy_2_clicked();

    void on_Fiction_2_clicked();

    void on_orderbtn_clicked();

    void on_cabinet_clicked();

    void on_pushButton_clicked();

    void on_cinform_clicked();

    void on_book_itemClicked(QTableWidgetItem *item);

    void on_erdered_itemClicked(QTableWidgetItem *item);




private:
    Ui::readerwindow *ui;
    QSqlDatabase db;
    UserInfo info;
    int idx;
};

#endif // READERWINDOW_H
