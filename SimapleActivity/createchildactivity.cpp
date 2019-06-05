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
    ui->spinBox->setValue(0);
    ui->doubleSpinBox->setValue(0);
}

void CreateChildActivity::on_pushButton_finished_clicked()
{
    QString name = ui->lineEdit->text();
    QString description = ui->textEdit->toPlainText();
    int join_time = ui->spinBox->value();
    double socre = ui->doubleSpinBox->value();
    if(name!=""&&description!="")
    {
        emit created(name,description,join_time,socre);
        this->close();
    }
    else
    {
        QMessageBox::warning(this,"错误","输入信息不能为空",QMessageBox::Ok);
    }

}
