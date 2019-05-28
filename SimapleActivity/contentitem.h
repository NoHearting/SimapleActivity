/**
  * @file
  * @brief 活动的主要显示项
  *
  *  显示在主页，主要显示每一个活动的信息
  * @version 1.0
  * @author zsj
  * @date 2019年5月11日11:50:10
*/

#ifndef CONTENTITEM_H
#define CONTENTITEM_H

#include <QWidget>
#include <QString>
#include <vector>
#include <QPixmap>
#include <QDebug>
#include <memory>
#include <QPaintEvent>
#include "user.h"

#include "signupactivity.h"
#include "getimage.h"
#include "readqstylesheet.h"

using namespace std;

namespace Ui {
class ContentItem;
}

class ContentItem : public QWidget
{
    Q_OBJECT

public:
    explicit ContentItem(QWidget *parent = 0);

    /// @brief 构造函数
    ///
    /// 接收一个活动的所有信息并创建此活动显示
    /// @param parent 父窗口指针
    /// @param urls 图片地址
    /// @param name 活动名称
    /// @param time 活动创建时间
    /// @param abstract 活动摘要
    /// @param join_num 活动参与人数
    ContentItem(QWidget *parent,const QVector<QString> &urls,QString name,QString time,QString abstract,int join_num,int id);

    ContentItem(QWidget *parent,int num);

    ContentItem(QWidget *parent,User user);
    ~ContentItem();


    /// @brief 获取整个显示框的高度
    int get_height();


    inline void set_id(int id){id_ = id;}
    inline void set_name(QString name){name_ = name;}
    inline void set_time(QString time){time_ = time;}
    inline void set_abstract(QString abstract){abstract_ = abstract;}
    inline void set_join_num(int join_num){join_num_ = join_num;}
private slots:
    void on_toolButton_sign_up_clicked();

private:
    Ui::ContentItem *ui;

    QVector<QString> urls_;  ///< 活动图片的地址
    QString name_;      ///< 活动名称
    QString time_;      ///< 活动创建时间
    QString abstract_;  ///< 摘要
    int join_num_;     ///< 参与人数
    int id_;           ///< 活动id

    int image_num_;

    QPixmap pix;

    shared_ptr<SignUpActivity> sign_activity_;   ///< 参加活动的报名界面

    shared_ptr<GetImage>get_image_;     ///< 获取图片信息


    void set_show_image();


protected:

    /// @brief 重写此函数，解决setStyleSheet函数无法设置样式的问题
    ///
    /// 不重写此函数无法用setStyleSheet读取qss文件的qss渲染内容
//    void paintEvent(QPaintEvent *);
};

#endif // CONTENTITEM_H
