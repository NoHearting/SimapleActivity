#include "mycreateactivity.h"
#include "ui_mycreateactivity.h"

MyCreateActivity::MyCreateActivity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyCreateActivity)
{
    ui->setupUi(this);
    qDebug()<<"构建MyCreateActivity";
//    QListWidgetItem * item = new QListWidgetItem();
//    ChildActivityItem *c_item = new ChildActivityItem(ui->listWidget_child,"哈哈","不知道");
//    c_item->setStyleSheet("background-color:rgb(192,250,214);");
//    item->setSizeHint(QSize(ui->listWidget_child->width(),100));
//    ui->listWidget_child->addItem(item);
//    ui->listWidget_child->setItemWidget(item,c_item);

//    QListWidgetItem * item2 = new QListWidgetItem();
//    ChildActivityItem *c_item2 = new ChildActivityItem(ui->listWidget_child,"嘿嘿","不清楚");
//    c_item2->setStyleSheet("background-color:rgb(192,250,214);");
//    item2->setSizeHint(QSize(ui->listWidget_child->width(),100));
//    ui->listWidget_child->addItem(item2);
//    ui->listWidget_child->setItemWidget(item2,c_item2);

//    QListWidgetItem * item3 = new QListWidgetItem();
//    ChildActivityItem *c_item3 = new ChildActivityItem(ui->listWidget_child,"嘿嘿","不清楚");
//    c_item3->setStyleSheet("background-color:rgb(192,250,214);");
//    item3->setSizeHint(QSize(ui->listWidget_child->width(),100));
//    ui->listWidget_child->addItem(item3);
//    ui->listWidget_child->setItemWidget(item3,c_item3);
}

MyCreateActivity::MyCreateActivity(QWidget *parent, QString activity_id, QString activity_name, QString activity_abstract):
    QWidget(parent),activity_id_(activity_id),activity_name_(activity_name),activity_abstract_(activity_abstract),
    ui(new Ui::MyCreateActivity)
{
    ui->setupUi(this);
    nam_.reset(new QNetworkAccessManager());

    ui->label_name->setText(activity_name_);
    ui->label_abstract->setText(activity_abstract_);
    connect(nam_.get(),&QNetworkAccessManager::finished,this,&MyCreateActivity::dealGetHttpData);
    QString url = QString("http://192.168.1.237:8080/test/activity/getAllChildActivity?aId=%1").arg(activity_id_);
    nam_->get(QNetworkRequest(QUrl(url)));
}

void MyCreateActivity::setUpdateHidden(bool flag)
{
    ui->pushButton->setHidden(flag);
}

MyCreateActivity::~MyCreateActivity()
{
    delete ui;
}

void MyCreateActivity::dealGetHttpData(QNetworkReply *reply)
{

    if(reply->error()==QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QJsonParseError json_error;
        QJsonDocument json_document = QJsonDocument::fromJson(bytes,&json_error);
        if(json_error.error!=QJsonParseError::NoError)
        {

            Cout<<"数据解析错误";
            return;
        }
        QJsonArray json_array;

        //  .......
        if(json_document.object().contains("childActivityData"))
        {
            json_array = json_document.object().value("childActivityData").toArray();
            for(int i = 0;i<json_array.size();++i)
            {
                // 显示子活动
                QJsonObject obj = json_array[i].toObject();
                QListWidgetItem * item = new QListWidgetItem();
                ChildActivityItem *c_item = new ChildActivityItem(ui->listWidget_child,
                                                                  obj.value("caName").toString(),
                                                                  obj.value("caDescription").toString());
                c_item->setStyleSheet("background-color:rgb(192,250,214);");
                item->setSizeHint(QSize(0,100));
                ui->listWidget_child->addItem(item);
                ui->listWidget_child->setItemWidget(item,c_item);
            }
        }
    }
    else
    {

    }
    reply->deleteLater();
}
