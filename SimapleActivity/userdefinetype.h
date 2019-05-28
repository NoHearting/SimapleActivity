#ifndef USERDEFINETYPE_H
#define USERDEFINETYPE_H

#include <QDialog>
#include <QString>

namespace Ui {
class UserDefineType;
}

class UserDefineType : public QDialog
{
    Q_OBJECT

public:
    explicit UserDefineType(QWidget *parent = 0);

    QString get_type()const;
    QString get_type_description()const;
    ~UserDefineType();

private slots:
    void on_pushButton_sure_clicked();

private:
    Ui::UserDefineType *ui;
signals:
    void addFinish(QString user_define,QString user_define_description);
};

#endif // USERDEFINETYPE_H
