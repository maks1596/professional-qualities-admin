#pragma once

#include <QObject>

class AddUserView;
class AddUserService;

class AddUserController : public QObject {
public:
    explicit AddUserController(QObject *parent = nullptr);

    AddUserView *getView() const;
    void setView(AddUserView *view);

    AddUserService *getService() const;
    void setService(AddUserService *service);

private:
    void onLoginChanged(const QString &login) const;
    void onPasswordChanged(const QString &password) const;
    void onRepeatPasswordChanged(const QString &repeatPassword) const;

    void onSaveUserButtonClicked() const;

    void addUser() const;

    AddUserView *m_view;
    AddUserService *m_service;
};
