#ifndef GETIMAGE_H
#define GETIMAGE_H

#include <QWidget>
#include <QByteArray>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <memory>
#include <QEventLoop>
#include <QUrl>
#include <QPainter>
#include <QSize>
#include <QBitmap>
#include <QPainterPath>
#include <QPixmap>

using namespace std;

class GetImage : public QWidget
{
    Q_OBJECT
public:
    explicit GetImage(QWidget *parent = 0);

    /// @brief 由url获取一张图片
    /// @param urls 图片资源的地址
    /// @return QPixmap 获取的图片
    QPixmap get_image(QUrl urls);

    /// @brief 将图片缩放为圆形
    /// @param pixmap 缩放的图片
    /// @param radius 缩放的尺寸
    /// @return QPixmap 一张新的图片
    static QPixmap get_round_image(QPixmap & pixmap,int radius);

signals:
    void ok();
    void not_ok();
public slots:

private:
    shared_ptr<QNetworkAccessManager>nam_;
    QByteArray data_;

    bool error = true;     ///< 获取图片是否正确
};

#endif // GETIMAGE_H
