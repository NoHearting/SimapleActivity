#include "mainactivity.h"

MainActivity::MainActivity()
{

    a_id_ = 0;
    u_id_ = 0;
    name_ = "默认活动";
    create_time_ = QDate::currentDate().toString("yyyy-MM-dd");
    dead_time_ = create_time_;
    participation_ = 0;
    abstract_ = "就是一个默认活动";
    description_ = "我也不清楚到底是什么活动";
    status_ = 0;
    notice_ = "今天谁也不知道";
    have_child_ = false;
    address_ = "重庆不知道大学";
    total_score_ = 0;

}

MainActivity::MainActivity(int a_id,QString name, QString dead_time, QString abstract, QString description, QString address):
    name_(name),dead_time_(dead_time),abstract_(abstract),description_(description),address_(address),a_id_(a_id)
{

}

MainActivity::MainActivity(int a_id, int u_id, QString name, QString create_time, QString dead_time, int participation, QString abstract, QString description, const QStringList & pic_path, int status, QString notice, bool have_child, int total_score):
    a_id_(a_id),u_id_(u_id),name_(name),create_time_(create_time),dead_time_(dead_time),participation_(participation),
    abstract_(abstract),description_(description),pic_path_(pic_path),status_(status),notice_(notice),
    have_child_(have_child),total_score_(total_score)
{

}

void MainActivity::reset(int u_id,QString name, QString dead_time, QString abstract, QString description, QString address,QString notice)
{
    name_ = name;
    dead_time_ = dead_time;
    abstract_ = abstract;
    description_ =description;
    address_ = address;
    u_id_ = u_id;
    notice_ = notice;
}

