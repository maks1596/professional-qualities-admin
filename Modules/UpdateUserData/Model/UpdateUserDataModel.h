#pragma once

#include "BaseService/BaseService.h"

class User;

class UpdateUserDataModel : public BaseService {
Q_OBJECT

public:
	UpdateUserDataModel(QObject *parent = nullptr);

	void patchUser(const User &user) const;

signals:
	void userPatched() const;
};
