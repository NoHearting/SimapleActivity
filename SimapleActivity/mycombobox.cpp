#include "mycombobox.h"

MyComboBox::MyComboBox(QWidget *parent) : QComboBox(parent)
{

}

void MyComboBox::focusInEvent(QFocusEvent *e)
{
    emit changeBkColor(false);
    QComboBox::focusInEvent(e);
}

void MyComboBox::focusOutEvent(QFocusEvent *e)
{
    emit changeBkColor(true);
    QComboBox::focusOutEvent(e);
}



