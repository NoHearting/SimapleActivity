#include "createchildactivity.h"
#include "ui_createchildactivity.h"

CreateChildActivity::CreateChildActivity(QString win_name,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateChildActivity)
{
    ui->setupUi(this);
    this->setWindowTitle(win_name);
}

CreateChildActivity::~CreateChildActivity()
{
    delete ui;
}

void CreateChildActivity::clear()
{
    ui->lineEdit->setText("");
    ui->textEdit->setText("");
}

void CreateChildActivity::on_pushButton_finished_clicked()
{
    QString name = ui->lineEdit->text();
    QString description = ui->textEdit->toPlainText();
    if(name!=""&&description!="")
    {
        emit created(name,description);
        this->close();
    }
    else
    {
        QMessageBox::warning(this,"错误","输入信息不能为空",QMessageBox::Ok);
    }

}
