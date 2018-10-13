#pragma once

#include "BaseService/BaseService.h"

class User;

class UsersService : public BaseService {
Q_OBJECT

public:
    UsersService(QObject *parent = nullptr);

public:
    void getUsers() const;
    void removeUser(int userId) const;

signals:
    void usersGot(const QList<User> &users);
    void userRemoved();

private slots:
    void jsonUsersGot(const QJsonArray &jsonUsers);
};
