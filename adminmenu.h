#ifndef ADMINMENU_H
#define ADMINMENU_H
#include <QDialog>
#include <vector>
#include <iostream>
#include <book.h>
#include <loginwindow.h>
#include <orders.h>
#include <storage.h>
#include <userinfo.h>
#include <string>
#include <QTableWidgetItem>
namespace Ui {
class adminmenu;
}

class adminmenu : public QDialog
{
    Q_OBJECT

public:


    explicit adminmenu(QWidget *parent = 0);

    void setDb( QSqlDatabase db)
    {
        this->db = db;
    }
    void setUserInfo(UserInfo info)
    {
        this->info = info;
    }
    ~adminmenu();
public slots:
    void setRowC(int id, int num_rows);
    // void setLabel(vector<QString> data);
    QString getValuefromT();
    void setLbl();
    QString getSelectedStatus();
    QString searchT();
    int getSelectedOrd();
    void insertBook(QList <book> books);
    bool isSelected();
private slots:
    void loadorders();
    void loadBook();
    void loadReaders();
    void on_readersBtn_clicked();

    void on_bookBtn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();


    void on_pushButton_3_clicked();

    void on_sortStatus_clicked();

    void on_soerYear_clicked();

    void on_sortAuth_clicked();

    void on_sortGenre_clicked();

    void on_sortName_clicked();

    //void on_book_2_itemPressed(QTableWidgetItem *item);

    void on_pushButton_5_clicked();

    void on_snam_clicked();


    void on_scard_clicked();

    void on_sstats_clicked();


    void on_accept_clicked();

    void on_close_clicked();

    void on_decline_clicked();

    void on_book_2_itemClicked(QTableWidgetItem *item);

    void on_orderss_itemClicked(QTableWidgetItem *item);

    void on_pushButton_6_clicked();


    void insertOrders(QList <orders> ord);

private:
    Ui::adminmenu *ui;
    QPalette darkPalette;
    QSqlDatabase db;


    book Book;
    UserInfo info;

};

#endif // ADMINMENU_H
