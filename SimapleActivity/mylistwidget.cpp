#include "mylistwidget.h"

MyListWidget::MyListWidget(QWidget * parent):
    QListWidget(parent)
{

    nam_.reset(new QNetworkAccessManager());
    connect(nam_.get(),&QNetworkAccessManager::finished,this,&MyListWidget::dealGetHttpData);


      //从服务器获取创建的主活动信息
//    QListWidgetItem * item = new QListWidgetItem();
//    MyCreateActivity * m_item = new MyCreateActivity();
//    m_item->setStyleSheet("background-color:rgb(248,246,242);");
//    this->addItem(item);
//    item->setSizeHint(QSize(this->width(),400));
//    this->setItemWidget(item,m_item);

//    QListWidgetItem * item2 = new QListWidgetItem();
//    MyCreateActivity * m_item2 = new MyCreateActivity();
//    m_item2->setStyleSheet("background-color:rgb(248,246,242);");
//    this->addItem(item2);
//    item2->setSizeHint(QSize(this->width(),400));
//    this->setItemWidget(item2,m_item2);

//    QListWidgetItem * item3 = new QListWidgetItem();
//    MyCreateActivity * m_item3 = new MyCreateActivity();
//    m_item3->setStyleSheet("background-color:rgb(248,246,242);");
//    this->addItem(item3);
//    item3->setSizeHint(QSize(this->width(),400));
//    this->setItemWidget(item3,m_item3);
//    qDebug()<<"构建MyListWidget";

    this->setStyleSheet(ReadQStyleSheet::readQss(":/qss/qss_mylistwidget.qss"));


}

void MyListWidget::showContent(QString name,int status)
{
    QString url = "http://192.168.1.237:8080/test/activity/getActivity";
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QNetworkReply * reply = nam_->post(request,QString("uName=%1&aStatus=%2").arg(name).arg(status).toUtf8());
    Cout<<"showContent";

}

void MyListWidget::dealGetHttpData(QNetworkReply *reply)
{
    if(reply->error()==QNetworkReply::NoError)
    {
        Cout<<"MyListWidget::dealGetHttpData";

        QByteArray bytes = reply->readAll();
        Cout<<QString(bytes);
        QJsonParseError json_error;
        QJsonDocument json_document = QJsonDocument::fromJson(bytes,&json_error);
        if(json_error.error!=QJsonParseError::NoError)
        {
            qDebug()<<"数据解析错误";
            return;
        }
        QJsonArray json_array;
        if(json_document.object().contains("participationData"))
        {
            json_array = json_document.object().value("participationData").toArray();
            for(int i = 0;i<json_array.size();i++)
            {
                QJsonObject obj = json_array[i].toObject();
                Cout<<obj.value("aId").toInt()<<"--"<<obj.value("aName").toString();
                QListWidgetItem * item = new QListWidgetItem(this);
                MyCreateActivity * m_item = new MyCreateActivity(0,
                                                                 QString::number(obj.value("aId").toInt()),
                                                                 obj.value("aName").toString(),
                                                                 obj.value("aAbstract").toString()
                                                                 );
//                MyCreateActivity * m_item = new MyCreateActivity();
                m_item->setStyleSheet("background-color:rgb(248,246,242);");
                this->addItem(item);
                item->setSizeHint(QSize(0,400));
                this->setItemWidget(item,m_item);
                Cout<<i;
            }
        }
        else
        {
            Cout<<"不包含participationData";
        }
    }
    else
    {
        QMessageBox::warning(this,"错误","未知错误",QMessageBox::Ok);
    }
    reply->deleteLater();
}

void MyListWidget::wheelEvent(QWheelEvent * e)
{

    int num_step = e->delta()/120;
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->value()-num_step);

    QListWidget::wheelEvent(e);
}

