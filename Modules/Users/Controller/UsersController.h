#pragma once

#include <QObject>

class UsersForm;
class UsersModel;
class UsersService;

class UsersController : public QObject {
    Q_OBJECT
public:
    UsersController(UsersForm *view,
                    UsersModel *model,
                    UsersService *service);

private slots:
    void onUserClicked(const QModelIndex &idx);
    void onUserDoubleClicked(const QModelIndex &idx);
    void onRemoveUserClicked(uint index);

private:
    void connectView();
    void connectService();

    UsersForm *m_view = nullptr;
    UsersModel *m_model = nullptr;
    UsersService *m_service = nullptr;
};
