#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
namespace Ui {
class loginWindow;
}

class loginWindow : public QDialog
{
    Q_OBJECT
public:

    void setDb(QSqlDatabase db)
    {
        this->db = db;
    }

public:

    explicit loginWindow(QWidget *parent = 0);
    ~loginWindow();

private slots:
 //   void on_pushButton_clicked();
    void validAdd();
    void on_LLoginLE_textChanged(const QString &arg1);

    void on_LpassLE_textChanged(const QString &arg1);

    void on_login_clicked();

    void on_singB_clicked();

private:
    Ui::loginWindow *ui;
       QSqlDatabase db;


};

#endif // LOGINWINDOW_H
