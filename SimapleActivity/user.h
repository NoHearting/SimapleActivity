/**
  * @file
  * @brief 用户信息
 */

#ifndef USER_H
#define USER_H

#include <QString>


class User
{
public:
    User();
    User(int id,QString name,QString pwd,QString signature,bool sex,QString headpath,QString phone,QString email);
    User(const User & obj);
    User & operator =(const User & rhs);
    bool operator ==(const User & rhs);

    inline int get_id(){return id_;}
    inline QString get_nickname(){return nickname_;}
    inline QString get_password(){return password_;}
    inline bool get_sex(){return sex_;}
    inline QString get_headpath(){return headpath_;}
    inline QString get_phone(){return phone_;}
    inline QString get_email(){return email_;}
    inline QString get_signature(){return signature_;}
private:
    int  id_;
    QString nickname_;
    QString password_;
    QString signature_;
    bool sex_;
    QString headpath_;
    QString phone_;
    QString email_;
};

#endif // USER_H
