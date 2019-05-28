#include "getimage.h"

GetImage::GetImage(QWidget *parent) : QWidget(parent)
{
    nam_.reset(new QNetworkAccessManager());
    connect(nam_.get(),&QNetworkAccessManager::finished,this,[=](QNetworkReply * reply){
        if(reply->error()==QNetworkReply::NoError)
        {
            data_ = reply->readAll();
            error = false;
            emit ok();

        }
        else
        {
            emit not_ok();
            error = true;
            data_.clear();
        }
        reply->deleteLater();
    });
}

QPixmap GetImage::get_image(QUrl urls)
{

    QEventLoop e;
    connect(this,&GetImage::ok,&e,&QEventLoop::quit);
    connect(this,&GetImage::not_ok,&e,&QEventLoop::quit);
    QNetworkReply * reply = nam_->get(QNetworkRequest(urls));
    e.exec();
    QPixmap pix;
    if(!error)
    {
        pix.loadFromData(data_);
    }
    else
    {
        pix.load(":/Main/C:/Users/ASUS/Pictures/Image/123.jpg");
    }

    return pix;
}

QPixmap GetImage::get_round_image(QPixmap &pixmap, int radius)
{
    if(pixmap.isNull())
    {
        return QPixmap();
    }
    QSize size(2*radius,2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0,0,size.width(),size.height(),Qt::white);
    painter.setBrush(QColor(0,0,0));
    painter.drawRoundedRect(0,0,size.width(),size.height(),99,99);

    QPixmap image = pixmap.scaled(size);
    image.setMask(mask);
    return image;
}

