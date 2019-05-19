#ifndef ADDREADER_H
#define ADDREADER_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class addReader;
}

class addReader : public QDialog
{
    Q_OBJECT

public:
    explicit addReader(QWidget *parent = 0);
    void setDb(QSqlDatabase db)
    {
        this->db = db;
    }
    ~addReader();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addReader *ui;
    QSqlDatabase db;
};

#endif // ADDREADER_H
