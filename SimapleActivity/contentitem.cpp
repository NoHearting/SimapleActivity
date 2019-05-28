#include "contentitem.h"
#include "ui_contentitem.h"

ContentItem::ContentItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContentItem)
{
    ui->setupUi(this);

}


// 和服务器交互主要用这个构造函数
ContentItem::ContentItem(QWidget *parent,const QVector<QString> &urls, QString name, QString time, QString abstract, int join_num,int id)
    :QWidget(parent),
     ui(new Ui::ContentItem),urls_(urls),name_(name),time_(time),abstract_(abstract),join_num_(join_num),id_(id)
{
    ui->setupUi(this);

    // 初始化参加活动界面
    this->setStyleSheet(ReadQStyleSheet::readQss(":/qss/qss_contentitem.qss"));
//    sign_activity_.reset(new SignUpActivity(0,id_));
//    sign_activity_->setHidden(true);
//    ui->widgetImageContent->setStyleSheet("border:1px solid red");
//    ui->toolButton_sign_up->setStyleSheet("color:red;");
    get_image_.reset(new GetImage());
    image_num_ = urls.size();
    qDebug()<<urls.size();
    set_show_image();
    QString default_image = ":/Login/C:/Users/ASUS/Pictures/Login/code.png";

    ui->label_name->setText(name_);
    ui->label_abstract->setText(abstract_);
    ui->label_create_time->setText(time_);
    ui->label_join_num->setText(QString("已参加%1人").arg(join_num_));

    if(image_num_ == 1)
    {
        //QPixmap * pixmap = new QPixmap(urls_[0]);
//        shared_ptr<QPixmap> pixmap(new QPixmap());
//        pixmap->loadFromData(get_image_->get_image(urls_[0]));
        QPixmap pixmap = get_image_->get_image(urls[0]);
        //pixmap->load(default_image);
//        if(pixmap.isNull())
//        {
//            qDebug()<<"NULL";
//            pixmap.reset(new QPixmap(default_image));
//        }
        QLabel * label = new QLabel(ui->widgetImageContent);
        int max = pixmap.height()>pixmap.width()?pixmap.height():pixmap.width();
        double x = max*1.0/300;
        QSize qsize(pixmap.width()/x,pixmap.height()/x);
        qDebug()<<qsize.height()<<"-----"<<qsize.width();
        pix = pixmap.scaled(qsize,Qt::KeepAspectRatio);
        label->setPixmap(pix);
    }
    else if(image_num_ == 2)
    {



//        shared_ptr<QPixmap>pixmap(new QPixmap());
//        shared_ptr<QPixmap>pixmap2(new QPixmap());
//        pixmap->loadFromData(get_image_->get_image(urls[0]));
//        pixmap2->loadFromData(get_image_->get_image(urls[1]));
//        QPixmap * pixmap = new QPixmap(default_image);
//        QPixmap * pixmap2 = new QPixmap(default_image);
        QPixmap pixmap = get_image_->get_image(urls[0]);
        QPixmap pixmap2 = get_image_->get_image(urls[1]);
//        if(pixmap->isNull())
//        {
//            qDebug()<<"NULL";
//            pixmap.reset(new QPixmap(default_image));
//            pixmap2.reset(new QPixmap(default_image));


//        }
        QLabel * label1 = new QLabel(ui->widgetImageContent);
        QLabel * label2 = new QLabel(ui->widgetImageContent);
        label1->setFixedSize(150,150);

        label2->setFixedSize(150,150);
        label2->move(155,0);

        label1->setPixmap(pixmap.scaled(label1->size()));
        label2->setPixmap(pixmap2.scaled(label2->size()));

    }
    else
    {
        int i = 0;
        int j = 0;
        int n = 0;
//        shared_ptr<QPixmap> pix(new QPixmap());
        QPixmap pix;

        while(n<image_num_&&n<9)
        {
            // 一次最多显示九张
            //QPixmap * pix = new QPixmap(urls_[n]);
            pix = get_image_->get_image(urls[i]);
            //pix->load(default_image);
//            if(pix->isNull())
//            {
//                qDebug()<<"NULL";
//                pix->loadFromData(default_image.toStdString().c_str());
//            }
            QLabel * label = new QLabel(ui->widgetImageContent);
            label->setFixedSize(100,100);
            label->setPixmap(pix.scaled(QSize(100,100)));
            label->move(j*105,i*105);
            qDebug()<<"["<<j<<","<<i<<"]";
            j = (j+1)%3;
            n++;
            if(n%3==0)
            {
                i++;
            }

        }

    }
}


// 测试
ContentItem::ContentItem(QWidget *parent, int num):
    QWidget(parent),
    ui(new Ui::ContentItem),
    image_num_(num)
{
    ui->setupUi(this);
    set_show_image();

//    sign_activity_.reset(new SignUpActivity(0,1));
//    sign_activity_->setHidden(true);
//    this->setStyleSheet(ReadQStyleSheet::readQss(":/qss/qss_contentitem.qss"));
//    qDebug()<<ReadQStyleSheet::readQss(":/qss/qss_contentitem.qss");
    if(image_num_ == 1)
    {
        QPixmap * pixmap = new QPixmap("C:/Users/ASUS/Pictures/Image/xyz.jpg");
        if(pixmap->isNull())
        {
            qDebug()<<"NULL";
            return;
        }
        QLabel * label = new QLabel(ui->widgetImageContent);
        int max = pixmap->height()>pixmap->width()?pixmap->height():pixmap->width();
        int x = max/300;
        QSize qsize(pixmap->width()/x,pixmap->height()/x);
        pix = pixmap->scaled(qsize,Qt::KeepAspectRatio);
        label->setPixmap(pix);
    }
    else if(image_num_ == 2)
    {
        QPixmap * pixmap = new QPixmap("C:/Users/ASUS/Pictures/Image/xyz.jpg");
        if(pixmap->isNull())
        {
            qDebug()<<"NULL";
            return;
        }
        QLabel * label1 = new QLabel(ui->widgetImageContent);
        QLabel * label2 = new QLabel(ui->widgetImageContent);
        label1->setFixedSize(150,150);

        label2->setFixedSize(150,150);
        label2->move(155,0);

        label1->setPixmap(pixmap->scaled(label1->size()));
        label2->setPixmap(pixmap->scaled(label2->size()));
    }
    else
    {
        int i = 0;
        int j = 0;
        int n = 0;
        while(n<image_num_&&n<=9)
        {
            QPixmap * pix = new QPixmap("C:/Users/ASUS/Pictures/Image/xyz.jpg");
            QLabel * label = new QLabel(ui->widgetImageContent);
            label->setFixedSize(100,100);
            label->setPixmap(pix->scaled(QSize(100,100)));
            label->move(j*105,i*105);
            qDebug()<<"["<<j<<","<<i<<"]";
            j = (j+1)%3;
            n++;
            if(n%3==0)
            {
                i++;
            }
        }

    }
}

ContentItem::ContentItem(QWidget *parent, User user)
{

}



ContentItem::~ContentItem()
{
    delete ui;
}

// 待修改
void ContentItem::set_show_image()
{
    if(image_num_==1)
    {
        ui->widgetImageContent->setFixedHeight(315);
    }
    else if(image_num_==2)
    {
        ui->widgetImageContent->setFixedHeight(155);
    }
    else if(image_num_>=3&&image_num_<=6)
    {
        ui->widgetImageContent->setFixedHeight(210);
    }
    else
    {
        ui->widgetImageContent->setFixedHeight(315);
    }
}

//void ContentItem::paintEvent(QPaintEvent * e)
//{
//    QStyleOption opt;
//    opt.initFrom(this);
//    QPainter p(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
//    QWidget::paintEvent(e);
//}

int ContentItem::get_height()
{
    return ui->widgetHead->height()+ui->widgetImageContent->height()+ui->widgetFoot->height();
}

void ContentItem::on_toolButton_sign_up_clicked()
{
    if(!sign_activity_)    //点击的时候再申请内存
    {
        sign_activity_.reset(new SignUpActivity(0,id_,name_));
        Cout<<"进入";
    }
    sign_activity_->show();
}
