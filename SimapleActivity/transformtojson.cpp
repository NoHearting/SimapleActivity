#include "transformtojson.h"

TransformToJson::TransformToJson()
{

}

QByteArray TransformToJson::activityToJson(const QString &uName, const MainActivity *main_activity,const QVector<QPair<QString, QString>> &field_list, const QVector<QPair<QString, QString> >& child_data)
{
    QJsonDocument json_doc;
    QJsonObject json_obj;
    json_obj.insert("uName",uName);

    //主活动信息对象
    QJsonObject json_main_act_obj;
    json_main_act_obj.insert("aName",main_activity->get_name());
    json_main_act_obj.insert("aDeadlineTime",main_activity->get_dead_time().toString("yyyy-MM-dd"));
    json_main_act_obj.insert("aParticipation",main_activity->get_participation());
    json_main_act_obj.insert("aAbstract",main_activity->get_abstract());
    json_main_act_obj.insert("aDescription",main_activity->get_description());
    json_main_act_obj.insert("aNotice",main_activity->get_notice());

    //报名表字段数组
    QJsonArray json_field_array;
    for(int i = 0;i<field_list.size();i++)
    {
        QJsonObject json_temp;
        json_temp.insert("name",field_list[i].first);
        json_temp.insert("notice",field_list[i].second);
        json_field_array.append(QJsonValue(json_temp));
        json_temp.remove("name");
        json_temp.remove("notice");
    }

    //子活动信息
    QJsonArray json_child_act_array;
    for(int i = 0;i<child_data.size();i++)
    {
        QJsonObject json_temp;
        json_temp.insert("caName",child_data[i].first);
        json_temp.insert("caDescription",child_data[i].second);
        json_child_act_array.append(QJsonValue(json_temp));
        json_temp.remove("caName");
        json_temp.remove("caDescription");
    }

    json_obj.insert("activity",QJsonValue(json_main_act_obj));
    json_obj.insert("fieldList",QJsonValue(json_field_array));
    json_obj.insert("childActivityList",QJsonValue(json_child_act_array));

    json_doc.setObject(json_obj);
    QByteArray bytes = json_doc.toJson(QJsonDocument::Compact);


    return bytes;

}

QByteArray TransformToJson::childActivityAndEntryFormToJson(const int a_id, const QList<QString> field_list, const QList<ChildActivityItem> &list_child_activity)
{

}



