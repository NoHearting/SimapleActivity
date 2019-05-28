#include "signupactivity.h"
#include "ui_signupactivity.h"

SignUpActivity::SignUpActivity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUpActivity)
{
    ui->setupUi(this);


}

SignUpActivity::SignUpActivity(QWidget *parent, int activity_id):
    QWidget(parent),
    ui(new Ui::SignUpActivity),activity_id_(activity_id)
{
    ui->setupUi(this);
    initWindowResource();
//    set_sign_up_item();
//    set_child_activity_item();

    nam_.reset(new QNetworkAccessManager());
    connect(nam_.get(),&QNetworkAccessManager::finished,this,&SignUpActivity::dealGetHttpData);

    connect(ui->listWidget_child_data,&QListWidget::itemClicked,this,[=](QListWidgetItem * item){
        qDebug()<<"点击了一下";
    });



}

SignUpActivity::SignUpActivity(QWidget *parent, int activity_id, QString name):
    QWidget(parent),
    ui(new Ui::SignUpActivity),activity_id_(activity_id),activity_name_(name)
{
    ui->setupUi(this);
    initWindowResource();


    ui->label_name->setText(QString("\"")+activity_name_+QString("\"")+QString("活动报名"));
    nam_.reset(new QNetworkAccessManager());
    connect(nam_.get(),&QNetworkAccessManager::finished,this,&SignUpActivity::dealGetHttpData);

//    set_sign_up_item();
//    set_child_activity_item();

    connect(ui->listWidget_child_data,&QListWidget::itemClicked,this,[=](QListWidgetItem * item){
        qDebug()<<"点击了一下";
    });
    Cout<<"完成";
}

void SignUpActivity::set_sign_up_item()
{
    //先获取信息
    QEventLoop e;
    QString url = QString("http://192.168.1.237:8080/test/manager/entryFields?aId=%1").arg(activity_id_);
    Cout<<url;
    status_ = 1;
    nam_->get(QNetworkRequest(QUrl(url)));
    connect(this,&SignUpActivity::sign_up_item,&e,&QEventLoop::quit);
    e.exec();
    Cout<<"发射SignUpActivity::set_sign_up_item";

//    QListWidgetItem * item = new QListWidgetItem();
//    SignUpItem * s_item = new SignUpItem(ui->listWidget_data,"学号");
//    item->setSizeHint(QSize(0,50));
//    ui->listWidget_data->addItem(item);
//    ui->listWidget_data->setItemWidget(item,s_item);

//    QListWidgetItem * item2 = new QListWidgetItem();
//    SignUpItem *s_item2 = new SignUpItem(ui->listWidget_data,"姓名");
//    item2->setSizeHint(QSize(0,50));
//    ui->listWidget_data->addItem(item2);
//    ui->listWidget_data->setItemWidget(item2,s_item2);

//    QListWidgetItem * item3 = new QListWidgetItem();
//    SignUpItem *s_item3 = new SignUpItem(ui->listWidget_data,"不知道是谁的姓名");
//    item3->setSizeHint(QSize(0,50));
//    ui->listWidget_data->addItem(item3);
//    ui->listWidget_data->setItemWidget(item3,s_item3);
}

void SignUpActivity::set_child_activity_item()
{
    QEventLoop e;
    //先从服务器获取信息
    Cout<<"activity_id_   "<<activity_id_;
    QString url = QString("http://192.168.1.237:8080/test/manager/getAllChildActivity?aId=%1").arg(activity_id_);
    status_ = 2;
    nam_->get(QNetworkRequest(QUrl(url)));
    Cout<<"发射SignUpActivity::set_child_activity_item";
    connect(this,&SignUpActivity::child_activity_item,&e,&QEventLoop::quit);
    e.exec();

//    QListWidgetItem * item = new QListWidgetItem();
//    ChildActivityItem * c_item = new ChildActivityItem(ui->listWidget_child_data,"不知道怎么回事","我也不知道");
//    c_item->set_hidden_no_use(true);
//    c_item->set_is_active(true);
//    c_item->setStyleSheet("background-color:rgb(248,246,242);");
//    item->setSizeHint(QSize(0,60));
//    ui->listWidget_child_data->addItem(item);
//    ui->listWidget_child_data->setItemWidget(item,c_item);

//    QListWidgetItem * item2 = new QListWidgetItem();
//    ChildActivityItem * c_item2 = new ChildActivityItem(ui->listWidget_child_data,"不知道怎么回事","我也不知道");
//    c_item2->set_hidden_no_use(true);
//    c_item2->set_is_active(true);
//    c_item2->setStyleSheet("background-color:rgb(248,246,242);");
//    item2->setSizeHint(QSize(0,60));
//    ui->listWidget_child_data->addItem(item2);
//    ui->listWidget_child_data->setItemWidget(item2,c_item2);

//    QListWidgetItem * item3 = new QListWidgetItem();
//    ChildActivityItem * c_item3 = new ChildActivityItem(ui->listWidget_child_data,"不知道怎么回事","我也不知道");
//    c_item3->set_hidden_no_use(true);
//    c_item3->setStyleSheet("#widget{background-color:rgb(248,246,242);}");
//    c_item3->set_is_active(true);
//    item3->setSizeHint(QSize(0,60));
//    ui->listWidget_child_data->addItem(item3);
//    ui->listWidget_child_data->setItemWidget(item3,c_item3);
}

void SignUpActivity::initWindowResource()
{
    this->setWindowFlags(Qt::FramelessWindowHint);   //设置窗口无边框
    this->setAttribute(Qt::WA_TranslucentBackground);  //设置主窗口背景透明
    this->setStyleSheet(ReadQStyleSheet::readQss(":/qss/qss_signupactivity.qss"));
//    qDebug()<<ReadQStyleSheet::readQss(":/qss/qss_signupactivity.qss");

    QGraphicsDropShadowEffect * shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0,0);   //阴影偏移量
    shadow->setColor(Qt::black);  //阴影颜色
    shadow->setBlurRadius(5);     //阴影的模糊半径
    ui->widget->setGraphicsEffect(shadow);

    ui->listWidget_child_data->setSelectionMode(QAbstractItemView::MultiSelection);   //设置可以多选


}

SignUpActivity::~SignUpActivity()
{
    delete ui;
}

void SignUpActivity::mouseMoveEvent(QMouseEvent * e)
{
    QPoint afterMovePos = e->globalPos();
    if(z_.x()!=0&&z_.y()!=0)
    {
        QPoint moveDis = afterMovePos-z_;
        move(moveDis);
    }
}

void SignUpActivity::mousePressEvent(QMouseEvent * e)
{
    QPoint currGlobalPos = e->globalPos();              //当前鼠标的全局位置
    QPoint currLocPos = this->geometry().topLeft();    //当前鼠标点击窗口的左上角坐标
    z_ = currGlobalPos-currLocPos;
}

void SignUpActivity::mouseReleaseEvent(QMouseEvent *)
{
    z_ = QPoint(0,0);
}

void SignUpActivity::dealGetHttpData(QNetworkReply *reply)
{
    if(reply->error()==QNetworkReply::NoError)
    {
        switch(status_)
        {
        case 1:
            dealActivityEntryForm(reply);
            break;
        case 2:
            dealChooseChildActivity(reply);
            break;
        case 3:
            break;
        default:
            break;
        }
    }

}

void SignUpActivity::dealActivityEntryForm(QNetworkReply * reply)
{

    QJsonParseError json_error;
    QByteArray bytes = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(bytes,&json_error);
    Cout<<bytes.data();
    if(json_error.error != QJsonParseError::NoError)
    {
        Cout<<"数据解析错误";
        emit sign_up_item();
        return;
    }
    if(json_doc.object().contains("fieldsInfo"))
    {
//        QJsonArray json_array = json_doc.object().value("fieldsInfo").toArray();

        QJsonObject obj = json_doc.object().value("fieldsInfo").toObject();
        auto json_map = obj.toVariantMap();

        for(int i = 0;i<json_map.size();i++)
        {

            QListWidgetItem * item = new QListWidgetItem();

            SignUpItem * s_item = new SignUpItem(ui->listWidget_data,
                                                 static_cast<QString>(json_map.keys()[i]),
                                                 json_map.values()[i].toString()
                                                 );
            item->setSizeHint(QSize(0,50));
            ui->listWidget_data->addItem(item);
            ui->listWidget_data->setItemWidget(item,s_item);
        }


    }

    reply->deleteLater();
    emit sign_up_item();
//    QListWidgetItem * item = new QListWidgetItem();
//    SignUpItem * s_item = new SignUpItem(ui->listWidget_data,"学号");
//    item->setSizeHint(QSize(0,50));
//    ui->listWidget_data->addItem(item);
//    ui->listWidget_data->setItemWidget(item,s_item);



}

void SignUpActivity::dealChooseChildActivity(QNetworkReply *reply)
{
    QByteArray bytes = reply->readAll();
    QJsonParseError json_error;
    Cout<<bytes.data();
    QJsonDocument json_document = QJsonDocument::fromJson(bytes,&json_error);
    if(json_error.error!=QJsonParseError::NoError)
    {
        Cout<<"数据解析错误";
        emit child_activity_item();
        return;
    }
    QJsonArray json_array;

    //  .......
    if(json_document.object().contains("childActivityMessagae"))
    {
        json_array = json_document.object().value("childActivityMessagae").toArray();
        for(int i = 0;i<json_array.size();++i)
        {
            QJsonObject obj = json_array[i].toObject();
            QListWidgetItem * item = new QListWidgetItem();
            ChildActivityItem * c_item = new ChildActivityItem(ui->listWidget_child_data,
                                                              obj.value("caName").toString(),
                                                              QString("数据库未添加摘要字段"));
            c_item->set_hidden_no_use(true);
            c_item->set_is_active(true);
            c_item->setStyleSheet("background-color:rgb(248,246,242);");
            item->setSizeHint(QSize(0,60));
            ui->listWidget_child_data->addItem(item);
            ui->listWidget_child_data->setItemWidget(item,c_item);
        }
    }

    reply->deleteLater();
    emit child_activity_item();
}

void SignUpActivity::on_toolButton_close_clicked()
{
    this->close();
}

void SignUpActivity::on_pushButton_post_clicked()
{
    //将数据上传到服务器

    //提取填写的报名信息
    QList<QPair<QString,QString>> list_data;
    for(int i = 0;i<ui->listWidget_data->count();i++)
    {
        QListWidgetItem * item = ui->listWidget_data->item(i);
        QWidget * widget = ui->listWidget_data->itemWidget(item);
        SignUpItem * sign = dynamic_cast<SignUpItem*>(widget);
        list_data.push_back(QPair<QString,QString>(sign->get_label_name(),sign->get_content()));
    }

    // 获取选择报名的子活动信息
    auto list_child_data = ui->listWidget_child_data->selectedItems();

    //不知道这里发送数据的格式
    Cout<<list_child_data.size();
}
