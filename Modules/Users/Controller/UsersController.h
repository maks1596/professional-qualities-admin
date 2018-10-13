#pragma once

#include <QObject>

class UsersForm;
class UsersModel;
class UsersService;

class UsersController : public QObject {
public:
    UsersController(QObject *parent = nullptr);

    UsersForm *getView() const;
    void setView(UsersForm *view);

    UsersModel *getModel() const;
    void setModel(UsersModel *model);

    UsersService *getService() const;
    void setService(UsersService *service);

private:
    void onUserClicked(const QModelIndex &idx);
    void onUserDoubleClicked(const QModelIndex &idx);
    void onRemoveUserClicked(uint index);

    UsersForm *m_view = nullptr;
    UsersModel *m_model = nullptr;
    UsersService *m_service = nullptr;
};
