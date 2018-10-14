#pragma once

#include <QObject>

#include "../Output/AddUserOutput.h"

class AddUserView;
class AddUserService;

class AddUserController : public AddUserOutput {
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

    void onExpertAssessmentChanged(int assessement);

    void onSaveUserButtonClicked() const;

    void addUser() const;

    AddUserView *m_view = nullptr;
    AddUserService *m_service = nullptr;
};
