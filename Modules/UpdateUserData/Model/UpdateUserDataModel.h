#pragma once

#include "BaseModel/BaseModel.h"

class User;

class UpdateUserDataModel : public BaseModel {
Q_OBJECT

public:
	UpdateUserDataModel(QObject *parent = nullptr);

	void patchUser(const User &user) const;

signals:
	void userPatched() const;
};
