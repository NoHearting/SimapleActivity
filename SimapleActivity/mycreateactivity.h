/**
  * @file
  * @brief 用来显示 用户创建的活动项
  *
  * 显示所有用户创建的活动信息
  * @version 1.0
  * @date 2019年5月23日11:58:40
  * @author zsj
  */

#ifndef MYCREATEACTIVITY_H
#define MYCREATEACTIVITY_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <memory>
#include <QListWidgetItem>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "childactivityitem.h"
#include "readqstylesheet.h"

using namespace std;

namespace Ui {
class MyCreateActivity;
}

class MyCreateActivity : public QWidget
{
    Q_OBJECT

public:
    explicit MyCreateActivity(QWidget *parent = 0);
    MyCreateActivity(QWidget *parent,QString activity_id,QString activity_name,QString activity_abstract);
    ~MyCreateActivity();

private:
    Ui::MyCreateActivity *ui;

    QString activity_id_;     ///< 主活动id
    QString activity_name_;
    QString activity_abstract_;

    shared_ptr<QNetworkAccessManager>nam_;    ///< 从服务器接收数据

    inline QString get_id(){return activity_id_;}


    /// @brief 从服务器获取数据
    void dealGetHttpData(QNetworkReply * reply);
};

#endif // MYCREATEACTIVITY_H
