#pragma once

#include "BaseModel/BaseModel.h"

class User;

class CreateUserModel : public BaseModel {
Q_OBJECT

public:
	CreateUserModel(QObject *parent = nullptr);

	void putUser(const User &user) const;
	void getProfessions() const;

signals:
	void userPut();
	void professionsGot(const QStringList &professions) const;

private slots:
	void jsonProfessionsGot(const QJsonArray &jsonProfessions) const;
};
