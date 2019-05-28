#include "userdefinetype.h"
#include "ui_userdefinetype.h"

UserDefineType::UserDefineType(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDefineType)
{
    ui->setupUi(this);
    this->setWindowTitle("自定义类型");
}

QString UserDefineType::get_type() const
{
    return ui->lineEdit->text();
}

QString UserDefineType::get_type_description() const
{
    return ui->textEdit->toPlainText();
}

UserDefineType::~UserDefineType()
{
    delete ui;
}

void UserDefineType::on_pushButton_sure_clicked()
{
    QString data = ui->lineEdit->text();
    QString data_des = ui->textEdit->toPlainText();
    if(data != ""&&data_des!="")
    {
        emit addFinish(data,data_des);
        ui->lineEdit->clear();
        ui->textEdit->clear();
        this->close();
    }
}
