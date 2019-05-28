#include "user.h"

User::User():id_(0)
{

}

User::User(int id, QString name, QString pwd, QString signature, bool sex, QString headpath, QString phone, QString email):
    id_(id),password_(pwd),nickname_(name),signature_(signature),sex_(sex),headpath_(headpath),phone_(phone),email_(email)
{

}

User::User(const User &obj):
    id_(obj.id_),password_(obj.password_),nickname_(obj.nickname_),signature_(obj.signature_),
    sex_(obj.sex_),headpath_(obj.headpath_),phone_(obj.phone_),email_(obj.email_)
{

}

User &User::operator =(const User & rhs)
{
    if(*this == rhs)
    {
        return *this;
    }
    id_ = rhs.id_;
    password_ = rhs.password_;
    nickname_ = rhs.nickname_;
    signature_ = rhs.nickname_;
    sex_ = rhs.sex_;
    headpath_ = rhs.headpath_;
    phone_ = rhs.phone_;
    email_ = rhs.email_;

    return *this;
}

bool User::operator ==(const User &rhs)  // 以id判断两个人是否相同
{
    return id_==rhs.id_;
}

