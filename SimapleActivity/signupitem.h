#ifndef SIGNUPITEM_H
#define SIGNUPITEM_H

#include <QWidget>
#include <QString>

namespace Ui {
class SignUpItem;
}

class SignUpItem : public QWidget
{
    Q_OBJECT

public:
    explicit SignUpItem(QWidget *parent = 0);
    SignUpItem(QWidget *parent,QString name,QString des = "请输入点东西");


    QString get_label_name();
    QString get_content();
    ~SignUpItem();

private:
    Ui::SignUpItem *ui;

};

#endif // SIGNUPITEM_H
