#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);




    // 接收点击左边菜单栏的信号
    connect(ui->listWidgetChoose,&QListWidget::itemClicked,this,&MainWidget::dealClickChoose);

    // 接收登录时候的信号
    login_ = shared_ptr<Login>(new Login());   // 初始化登录界面
    login_->show();
    connect(login_.get(),&Login::isOk,this,[=](User user){
        initListMainContent();   //初始化主要内容界面

        user_ = user;


        //string str = user_.get_headpath().toStdString();
        //std.substr

//        user_head_pic_.loadFromData(get_image_->get_image(QUrl(user_.get_headpath())));
        user_head_pic_ = get_image_->get_image(QUrl(user_.get_headpath()));

        QPixmap t = user_head_pic_.scaled(40,40);
        ui->label_small_menu_head->setPixmap(GetImage::get_round_image(t,20));


        ui->toolButtonUserSet->setText(user_.get_nickname()+"  ▼");   // 设置小菜单的标题，就是用户名

        // 设置小菜单属性



        // 用户小菜单界面




        choose_.reset(new UserInfoChoose(ui->widgetInner,user_head_pic_,user_.get_nickname(),"10","5"));
        choose_->setHidden(true);
        connect(choose_.get(),&UserInfoChoose::userSet,this,[=](int flag){

            if(flag==1)  // 转到个人设置
            {
                ui->stackedWidget_main->setCurrentIndex(5);
                // 隐藏小菜单
                choose_->setHidden(true);
//                is_show_small_menu_ = !is_show_small_menu_;
                QPixmap t = user_head_pic_.scaled(80,80);

                //当要看设置的时候再把数据填入
                ui->label_user_set_head->setPixmap(GetImage::get_round_image(t,40));
                ui->label_user_set_name->setText(user_.get_nickname());
                ui->textEdit_user_set_signature->setText(user_.get_signature());
                ui->lineEdit_user_set_email->setText(user_.get_email());
                ui->lineEdit_user_set_phone->setText(user_.get_phone());
                ui->lineEdit_user_set_pwd->setText(user_.get_password());
                if(user_.get_sex()==true)
                {
                    ui->radioButton_user_set_man->setChecked(true);
                }
                else
                {
                    ui->radioButton_user_set_woman->setChecked(true);
                }
            }
        });

        this->show();   // 界面初始化完成之后再显示
    });

    // 处理添加子活动的信号
    create_child_activity_.reset(new CreateChildActivity("创建子活动"));
    connect(create_child_activity_.get(),&CreateChildActivity::created,this,&MainWidget::dealCreateChildActivity);


    // 处理自定义报名表类型信号
    user_define_.reset(new UserDefineType());
    connect(user_define_.get(),&UserDefineType::addFinish,this,[=](QString data,QString data_des){
        QListWidgetItem * item = new QListWidgetItem(ui->listWidget_userdefined);
        UserDefineTypeShow * u_item = new UserDefineTypeShow(ui->listWidget_userdefined,data,data_des);
        ui->listWidget_userdefined->addItem(item);
        item->setSizeHint(QSize(0,40));
        ui->listWidget_userdefined->setItemWidget(item,u_item);
    });


    // 处理初始化活动主界面的的信号  添加所有活动
    nam_.reset(new QNetworkAccessManager());
    connect(nam_.get(),&QNetworkAccessManager::finished,this,&MainWidget::dealGetHttpData);

    get_image_.reset(new GetImage());

    initWinResource();
    initListChoose();

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::mouseMoveEvent(QMouseEvent * e)
{
    QPoint afterMovePos = e->globalPos();
    if(z_.x()!=0&&z_.y()!=0)
    {
        QPoint moveDis = afterMovePos-z_;
        move(moveDis);
    }
}

void MainWidget::mousePressEvent(QMouseEvent * e)
{
    QPoint currGlobalPos = e->globalPos();              //当前鼠标的全局位置
    QPoint currLocPos = this->geometry().topLeft();    //当前鼠标点击窗口的左上角坐标
    z_ = currGlobalPos-currLocPos;

}

void MainWidget::mouseReleaseEvent(QMouseEvent *)
{
    z_ = QPoint(0,0);
}

void MainWidget::initWinResource()
{
    this->setWindowFlags(Qt::FramelessWindowHint);   //设置窗口无边框
    this->setAttribute(Qt::WA_TranslucentBackground);  //设置主窗口背景透明
    this->setStyleSheet(ReadQStyleSheet::readQss(":/qss/qss_main.qss"));

    QGraphicsDropShadowEffect * shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0,0);   //阴影偏移量
    shadow->setColor(Qt::black);  //阴影颜色
    shadow->setBlurRadius(5);     //阴影的模糊半径
    ui->widgetInner->setGraphicsEffect(shadow);
    z_ = QPoint(0,0);


    // 初始化信息
    create_activity_info_[0]="         ";
    create_activity_info_[1]="创建主活动";
    create_activity_info_[2]="创建子活动";
    create_activity_info_[3]="创建报名表";
    create_activity_info_[4]="         ";

    base_type_data_["姓名"] = "请输入姓名";
    base_type_data_["电话"] = "请输入电话";
    base_type_data_["身份证号码"] = "请输入身份证号码";
    base_type_data_["邮箱"] = "请输入邮箱";
    base_type_data_["性别"] = "请填写性别（男，女）";
    base_type_data_["QQ"] = "请输入QQ";
    base_type_data_["微信"] = "请输入微信";

    //初始化子菜单
    base_.reset(new QLabel(ui->MainPage));  // 初始主页为父窗口
    base_->setHidden(true);       //初始影藏
    base_->setFixedSize(300,370);   // 设置大小匹配子菜单大小


    // 主活动对象  创建时用来保存该活动信息
    main_activity_.reset(new MainActivity());





    //base_->move(0,50);
    //base_->setStyleSheet("background-color:red;");

    // 初始化用户右上角的选择按钮
    //qDebug()<<user_.get_nickname();


    ui->listWidgetChoose->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // 关闭水平滚动条
    ui->listWidgetMainContent->setVerticalScrollMode(QListWidget::ScrollPerPixel);   //设置垂直滚动条以像素滚动
//    ui->listWidgetMainContent->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //关闭活动界面的水平滚动条
    ui->listWidgetMainContent->verticalScrollBar()->setSingleStep(1);        // 每次滚动10px
    //ui->widgetMainPageNav->setStyleSheet("background-color:rgb(233,233,233);border-bottom:1px solid black;");

    QStringList slist{QString("姓名"),QString("电话"),QString("身份证号码"),QString("邮箱"),QString("性别"),QString("QQ"),QString("微信")};
    ui->listWidget_base_type->addItems(slist);
    ui->listWidget_base_type->setSelectionMode(QAbstractItemView::MultiSelection);
}

void MainWidget::initListChoose()
{
    //主页
    QListWidgetItem * item = new QListWidgetItem();
    ui->listWidgetChoose->addItem(item);
    item->setSizeHint(QSize(200,30));
    ui->listWidgetChoose->setItemWidget(item,new WidgetItem(ui->listWidgetChoose,":/Login/C:/Users/ASUS/Pictures/Image/yyy.jpg","主页"));

    //我创建的
    QListWidgetItem * item2 = new QListWidgetItem();
    ui->listWidgetChoose->addItem(item2);
    item2->setSizeHint(QSize(200,30));
    ui->listWidgetChoose->setItemWidget(item2,new WidgetItem(ui->listWidgetChoose,":/Login/C:/Users/ASUS/Pictures/Image/yyy.jpg","我创建的"));

    // 排行榜
    QListWidgetItem * item3 = new QListWidgetItem();
    ui->listWidgetChoose->addItem(item3);
    item3->setSizeHint(QSize(200,30));
    ui->listWidgetChoose->setItemWidget(item3,new WidgetItem(ui->listWidgetChoose,":/Login/C:/Users/ASUS/Pictures/Image/yyy.jpg","排行榜"));


    // 动态
    QListWidgetItem * item4 = new QListWidgetItem();
    ui->listWidgetChoose->addItem(item4);
    item4->setSizeHint(QSize(200,30));
    ui->listWidgetChoose->setItemWidget(item4,new WidgetItem(ui->listWidgetChoose,":/Login/C:/Users/ASUS/Pictures/Image/yyy.jpg","动态"));


    // 设置
    QListWidgetItem * item5 = new QListWidgetItem();
    ui->listWidgetChoose->addItem(item5);
    item5->setSizeHint(QSize(200,30));
    ui->listWidgetChoose->setItemWidget(item5,new WidgetItem(ui->listWidgetChoose,":/Login/C:/Users/ASUS/Pictures/Image/yyy.jpg","设置"));

}

void MainWidget::initListMainContent()
{

    QUrl url("http://192.168.1.237:8080/test/activity/getAllActivity");

    //QNetworkReply * reply = nam_->get(QNetworkRequest(url));



    QListWidgetItem * item = new QListWidgetItem();
    ContentItem * c_item = new ContentItem(ui->listWidgetMainContent,2);
    c_item->setStyleSheet("background-color:rgb(248,246,242);");
    c_item->setStyleSheet(ReadQStyleSheet::readQss(":/qss/qss_contentitem.qss"));
    ui->listWidgetMainContent->addItem(item);
    ui->listWidgetMainContent->setItemWidget(item,c_item);
    item->setSizeHint(QSize(ui->listWidgetMainContent->width(),c_item->get_height()));

    QListWidgetItem * item2 = new QListWidgetItem();
    ContentItem * c_item2 = new ContentItem(ui->listWidgetMainContent,1);
    c_item2->setStyleSheet(ReadQStyleSheet::readQss(":/qss/qss_contentitem.qss"));
    ui->listWidgetMainContent->addItem(item2);
    ui->listWidgetMainContent->setItemWidget(item2,c_item2);
    item2->setSizeHint(QSize(ui->listWidgetMainContent->width(),c_item2->get_height()));

    QListWidgetItem * item3 = new QListWidgetItem();
    ContentItem * c_item3 = new ContentItem(ui->listWidgetMainContent,7);
    c_item3->setStyleSheet(ReadQStyleSheet::readQss(":/qss/qss_contentitem.qss"));
    ui->listWidgetMainContent->addItem(item3);
    ui->listWidgetMainContent->setItemWidget(item3,c_item3);
    item3->setSizeHint(QSize(ui->listWidgetMainContent->width(),c_item3->get_height()));
}

void MainWidget::setMainContent(QNetworkReply *reply)
{
    if(reply->error()==QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QString string = QString::fromUtf8(bytes);
        qDebug()<<string;


        QJsonParseError json_error;
        QJsonDocument json_document = QJsonDocument::fromJson(bytes,&json_error);
        if(json_error.error!=QJsonParseError::NoError)
        {
            qDebug()<<"数据解析错误";
            return;
        }
        QJsonArray json_array;
        QVector<QString> images;
        if(json_document.object().contains("activityData"))
        {
            qDebug()<<"包含此元素";
            json_array = json_document.object().value("activityData").toArray();

            for(int i = 0;i<json_array.size();i++)
            {
                QJsonObject obj = json_array.at(i).toObject();

                images.push_back(obj.value("aPicturePath").toString()); // 图片不止一张
                QListWidgetItem * item = new QListWidgetItem();
                    ContentItem * c_item = new ContentItem(ui->listWidgetMainContent,
                                                           images,
                                                           obj.value("aName").toString(),
                                                           obj.value("aDeadlineTime").toString(),
                                                           obj.value("aAbstract").toString(),
                                                           obj.value("aParticipation").toInt(),
                                                           obj.value("aId").toInt()
                                                           );
                Cout<<"id    "<<obj.value("aId").toInt()<<"    aName"<<obj.value("aName").toString();
                //ContentItem * c_item = new ContentItem(1,ui->listWidgetMainContent,images,"","","",1);
                //ContentItem * c_item = new ContentItem(ui->listWidgetMainContent,User());
                c_item->setStyleSheet("background-color:rgb(248,246,242);");
                c_item->setStyleSheet(ReadQStyleSheet::readQss(":/qss/qss_contentitem.qss"));
                ui->listWidgetMainContent->addItem(item);
                ui->listWidgetMainContent->setItemWidget(item,c_item);
                item->setSizeHint(QSize(0,c_item->get_height()));   // 此处宽的设置为0不会出问题
                qDebug()<<ui->listWidgetMainContent->width()<<"------------------------------"<<item->sizeHint().width();
                images.clear();
            }
        }
    }
    else
    {

    }
    reply->deleteLater();
}


void MainWidget::on_toolButtonClose_clicked()
{
    this->close();
}



void MainWidget::on_toolButtonUserSet_clicked()
{
    /*
      点击后将选择设置界面显示到按钮的正下方
      */
    if(choose_->isHidden())   //如果小菜单隐藏
    {
        //每次显示小菜单都将底层托举的QLabel父对象指定为当前的StackWidget中的页面
        base_->setParent(ui->stackedWidget_main->currentWidget());
        QSize s = ui->widgetInner->size();
        base_->move(ui->stackedWidget_main->width()-450,0);
        base_->show();
        choose_->move(s.width()-450,45);

        qDebug()<<"["<<s.width()<<","<<s.height()<<"]";
        choose_->show();
//        is_show_small_menu_ = !is_show_small_menu_;
    }
    else
    {
        choose_->setHidden(true);
        base_->setHidden(true);
//        is_show_small_menu_ = !is_show_small_menu_;
    }
}

void MainWidget::on_toolButtonMax_clicked()
{
    if(isMax == false)
    {
        this->showMaximized();
        isMax = !isMax;
    }
    else
    {
        this->showNormal();
        isMax = !isMax;
    }
    if(!choose_->isHidden())
    {
        QSize s = ui->widgetInner->size();
        choose_->move(s.width()-450,45);
        base_->move(ui->stackedWidget_main->width()-450,0);
    }
}

void MainWidget::on_toolButtonMin_clicked()
{
    this->showMinimized();
}

void MainWidget::dealClickChoose(QListWidgetItem * current)
{
    QWidget * currWidget = current->listWidget()->itemWidget(current);
    WidgetItem * wi = dynamic_cast<WidgetItem*>(currWidget);

    int n = ui->listWidgetChoose->count();
    for(int i = 0;i<n;i++)    // 貌似循环有点多余
    {
        QListWidgetItem * item = ui->listWidgetChoose->item(i);
        QWidget * ite = item->listWidget()->itemWidget(item);     //语句可精简
        WidgetItem * it = dynamic_cast<WidgetItem*>(ite);
        it->set_activity(false);
        if(*it == *wi)
        {

            if(it->get_name()=="我创建的")
            {
                if(ui->listWidget_my_create->count()<1)
                {
                    ui->listWidget_my_create->showContent(user_.get_nickname(),-1);   //此处的名字先做测试用
                }
            }

            ui->stackedWidget_main->setCurrentIndex(i);

            // 子菜单的底层QLabel操作
            base_->setParent(ui->stackedWidget_main->currentWidget());

            // false 是因为点击显示之后is_show_small_menu_就为false，此时如果换页面，要保证其能显示
            if(!choose_->isHidden())
            {
                base_->show();
            }
        }
    }
    wi->set_activity(true,"rgb(72,168,119);");

}

void MainWidget::dealCreateChildActivity(QString name, QString decription)
{
    QListWidgetItem * item = new QListWidgetItem();
    ChildActivityItem * c_item = new ChildActivityItem(ui->listWidget_child_activity,name,decription);
    item->setSizeHint(QSize(ui->listWidget_child_activity->width(),100));
    ui->listWidget_child_activity->addItem(item);
    ui->listWidget_child_activity->setItemWidget(item,c_item);
}

void MainWidget::dealGetHttpData(QNetworkReply *reply)
{
    // 状态码
    int statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(statusCodeV!=200)
    {
        ui->listWidgetMainContent->addItem(QString("加载数据出错，请刷新"));
        return;
    }
    qDebug()<<statusCodeV;
    QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    switch(CURRENT_TYPE)
    {
    case AUTO_MAIN_ACT:
        setMainContent(reply);   // 将从服务器获取的所有活动数据显示到界面
        break;
    case UPDATE_MAIN_ACT:
        setMainContent(reply);  // 更新显示
        break;
    case CREATE_ACT:

        break;
    case SIGN_UP_ACT:
        break;
    case USER_CREATED:
        break;
    default:
        break;
    }


}

void MainWidget::on_toolButton_create_activity_clicked()
{
    ui->stackedWidget_main->setCurrentIndex(6);
}

void MainWidget::on_toolButton_next_step_clicked()
{
    // 0
    int current_index = ui->stackedWidget_create_activity->currentIndex();
    if(current_index<2)
    {
        ui->stackedWidget_create_activity->setCurrentIndex(current_index+1);
        ui->label_current->setText(create_activity_info_[current_index+2]);
        ui->label_last->setText(create_activity_info_[current_index+1]);
        ui->label_next->setText(create_activity_info_[current_index+3]);
    }
}

void MainWidget::on_toolButton_last_step_clicked()
{

    int current_index = ui->stackedWidget_create_activity->currentIndex();
    if(current_index>0)
    {
        ui->stackedWidget_create_activity->setCurrentIndex(current_index-1);
        ui->label_current->setText(create_activity_info_[current_index]);
        ui->label_last->setText(create_activity_info_[current_index-1]);
        ui->label_next->setText(create_activity_info_[current_index+1]);
    }
}

void MainWidget::on_pushButton_finished_clicked()
{
    QString name = ui->lineEdit_name->text();
    if(name=="")
    {
        QMessageBox::warning(this,"错误","活动名称不能为空",QMessageBox::Ok);
        return;
    }
    QString abstract = ui->textEdit_abstract->toPlainText();
    if(abstract=="")
    {
        QMessageBox::warning(this,"错误","摘要不能为空",QMessageBox::Ok);
        return;
    }
    QString address = ui->lineEdit_address->text();
    if(address=="")
    {
        QMessageBox::warning(this,"错误","活动地点不能为空",QMessageBox::Ok);
        return;
    }
    QDate current_date = QDate::currentDate();
    QDate date = ui->dateEdit_date->date();
    if(current_date>date)
    {
        QMessageBox::warning(this,"错误","时光不能倒流（日期设置错误）",QMessageBox::Ok);
        return;
    }
    QString description = ui->textEdit_decription->toPlainText();
    if(description=="")
    {
        QMessageBox::warning(this,"错误","活动描述不能为空",QMessageBox::Ok);
        return;
    }
    QString notice = ui->lineEdit_notice->text();
    if(notice=="")
    {
        QMessageBox::warning(this,"错误","活动公告不能为空",QMessageBox::Ok);
        return;
    }

    main_activity_->reset(1,name,date,abstract,description,address,notice);

    if(ui->listWidget_child_activity->count()<1)  // 当第一次跳转到后面的页面的时候
    {
        //  默认主活动为第一条子活动
        QListWidgetItem * item = new QListWidgetItem();
        ChildActivityItem * c_item = new ChildActivityItem(ui->listWidget_child_activity,name,abstract);
        item->setSizeHint(QSize(ui->listWidget_child_activity->width(),100));
        ui->listWidget_child_activity->addItem(item);
        ui->listWidget_child_activity->setItemWidget(item,c_item);

    }
    else
    {
        QListWidgetItem * item = ui->listWidget_child_activity->item(0);
        QWidget * it = ui->listWidget_child_activity->itemWidget(item);
        ChildActivityItem * c_item = dynamic_cast<ChildActivityItem*>(it);
        c_item->reset(name,abstract);

    }

    on_toolButton_next_step_clicked();


}

void MainWidget::on_pushButton_add_child_activity_clicked()
{

    create_child_activity_->show();
    create_child_activity_->clear();
}

void MainWidget::on_pushButton_create_finish_clicked()
{
    //  传递给服务器数据

    // 取出所有确定的子活动的信息

    for(int i = 0;i<ui->listWidget_child_activity->count();i++)
    {
        QListWidgetItem * item = ui->listWidget_child_activity->item(i);
        QWidget * widget = ui->listWidget_child_activity->itemWidget(item);
        ChildActivityItem * c_item = dynamic_cast<ChildActivityItem*>(widget);
        child_activity_vector_.push_back(QPair<QString,QString>(c_item->get_name(),c_item->get_abstract()));
    }
//    for(QPair<QString,QString> pair:child_activity_vector_)
//    {
//        qDebug()<<pair.first<<pair.second;
//    }



    auto list_base_type = ui->listWidget_base_type->selectedItems();
//    for(int i = 0;i<list.size();i++)
//    {
//        qDebug()<<static_cast<QString>(list[i]->text());
//    }

    QList<QListWidgetItem*> list_user_define_type;



    QVector<QPair<QString,QString>> v_activity_data;
    // 添加基础类型

    for(int i = 0;i<list_base_type.size();i++)
    {
        v_activity_data.push_back(QPair<QString,QString>(
                                      list_base_type[i]->text(),
                                      base_type_data_[list_base_type[i]->text()]));
    }

    // 添加自定义类型
    if(ui->listWidget_userdefined->count()>0)
    {
        for(int i = 0;i<ui->listWidget_userdefined->count();++i)
        {
            QListWidgetItem * item = ui->listWidget_userdefined->item(i);
            QWidget * widget = ui->listWidget_userdefined->itemWidget(item);
            UserDefineTypeShow * u_item = dynamic_cast<UserDefineTypeShow*>(widget);
            v_activity_data.push_back(QPair<QString,QString>(
                                          u_item->get_type(),
                                          u_item->get_type_description()));
        }

//        for(int i = 0;i<list_user_define_type.size();++i)
//        {
//            qDebug()<<list_user_define_type[i]->text();
//        }
    }


    //创建活动的接口不能分开


    // 将主活动数据转化为json格式
//    QByteArray bytes = TransformToJson::mainActivityToJson("aaa",*main_activity_);

    QByteArray bytes = TransformToJson::activityToJson(
                user_.get_nickname(),
                main_activity_.get(),
                v_activity_data,
                child_activity_vector_);
    Cout<<bytes.data();
    //  将子活动数据和报名表数据转化为json格式


    // 发送服务器请求
    QString url = "http://192.168.1.237:8080/test/activity/createActivity";
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    nam_->post(request,bytes);

}

void MainWidget::on_toolButton_add_user_define_clicked()
{
    user_define_->show();
}

void MainWidget::on_pushButton_create_child_act_clicked()
{



    on_toolButton_next_step_clicked();

}

void MainWidget::on_toolButton_update_clicked()
{
    ui->listWidgetMainContent->clear();
    Cout<<"on_toolButton_update_clicked"<<"----"<<ui->listWidgetMainContent->width();
    CURRENT_TYPE = UPDATE_MAIN_ACT;
    QUrl url("http://192.168.1.237:8080/test/activity/getAllActivity");
    QNetworkReply * reply = nam_->get(QNetworkRequest(url));
}
