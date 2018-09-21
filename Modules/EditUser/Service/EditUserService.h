#pragma once

#include "BaseService/BaseService.h"

class User;

class EditUserService : public BaseService {
    Q_OBJECT
public:
    EditUserService(QObject *parent = nullptr);

    void patchUser(const User &user);

signals:
    void userPatched();
};
