#pragma once

#include "BaseService/BaseService.h"

class User;

class UsersModel : public BaseService {
Q_OBJECT

public:
	UsersModel(QObject *parent = nullptr);

public:
	void getUsers() const;
	void getUser(int userId) const;
	void deleteUser(int userId) const;

signals:
	void usersGot(const QList<User> &users);
	void userGot(const User &user);
	void userDeleted();

private slots:
	void jsonUsersGot(const QJsonArray &jsonUsers);
	void jsonUserGot(const QJsonObject &jsonUser);
};
