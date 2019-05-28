/**
  * @file
  * @brief 创建子活动中的一个子活动项
  *
  * 显示子活动的页面
  * @version 1.0
  * @date 2019年5月14日15:41:03
  * @author zsj
  */

#ifndef CHILDACTIVITYITEM_H
#define CHILDACTIVITYITEM_H

#include <QWidget>
#include <QDate>
#include <memory>
#include <QToolButton>

#include "createchildactivity.h"

namespace Ui {
class ChildActivityItem;
}

class ChildActivityItem : public QWidget
{
    Q_OBJECT

public:
    explicit ChildActivityItem(QWidget *parent = 0);
    ChildActivityItem(QWidget *parent,QString child_activity_name,QString child_activit_abstract);
    ChildActivityItem(QWidget *parent, QString child_activity_name, QString child_activit_abstract,int id);
    /// @brief 重新设置该子活动信息
    void reset(QString name,QString abstract);

    /// @brief 设置修改活动信息这个按钮是否显示
    void set_hidden_button(bool flag);

    /// @brief 设置日期标签是否显示
    void set_hidden_label(bool flag);

    /// @brief 设置一些不用的控件隐藏
    void set_hidden_no_use(bool flag);

    inline void set_is_active(bool flag){is_active_ = flag;}

    inline QString get_name(){return child_activity_name_;}
    inline QString get_abstract(){return child_activit_abstract_;}
    ~ChildActivityItem();

private slots:

    void on_pushButton_update_clicked();

private:
    Ui::ChildActivityItem *ui;

    bool is_active_;  ///< 标志   点击之后改不改变背景颜色
    bool changed_ = false;

    QString child_activity_name_;       ///< 子活动名
    QString child_activit_abstract_;    ///< 子活动摘要
    int ca_id_;        ///< 子活动id


    std::shared_ptr<CreateChildActivity> update_;   ///< 创建子活动界面

    /// @brief 初始化界面资源和配置
    void initWidgetResource();
protected:

    void mousePressEvent(QMouseEvent *);


};

#endif // CHILDACTIVITYITEM_H
