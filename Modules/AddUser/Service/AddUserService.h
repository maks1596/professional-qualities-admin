#pragma once

#include "BaseService/BaseService.h"

class User;

class AddUserService : public BaseService {
    Q_OBJECT
public:
    explicit AddUserService(QObject *parent = nullptr);

    void addUser(const User &user) const;

signals:
    void userAdded() const;
};
