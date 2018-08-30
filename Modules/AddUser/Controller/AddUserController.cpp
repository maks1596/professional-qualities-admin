#include "AddUserController.h"

#include <QDate>

#include "../View/AddUserView.h"
#include "../Service/AddUserService.h"
#include "Forms/UserDataForm/PasswordsHintStatus.h"

//  :: Constants ::

const QString LOGIN_IS_REQUIRED_TOOL_TIP = "Для создания пользователя необходимо ввести логин";

const QDate MAXIMUM_BIRTDATE = QDate::currentDate();

const int MINIMUM_EXPERT_ASSESSMENT = -1;
const int MAXIMUM_EXPERT_ASSESSMENT = 100;

//  :: Lifecycle ::

AddUserController::AddUserController(QObject *parent)
    : QObject(parent)
{ }

//  :: Public accessors ::
//  :: View ::
AddUserView *AddUserController::getView() const {
    return m_view;
}
void AddUserController::setView(AddUserView *view) {
    m_view = view;

    connect(view, &AddUserView::loginChanged,
            this, &AddUserController::onLoginChanged);
    connect(view, &AddUserView::passwordChanged,
            this, &AddUserController::onPasswordChanged);
    connect(view, &AddUserView::repeatPasswordChanged,
            this, &AddUserController::onRepeatPasswordChanged);

    view->setMaximumBirtdate(MAXIMUM_BIRTDATE);

    connect(view, &AddUserView::expertAssessmentChanged,
            this, &AddUserController::onExpertAssessmentChanged);
    view->setMaximumExpertAssessment(MAXIMUM_EXPERT_ASSESSMENT);
    view->setMinimumExpertAssessment(MINIMUM_EXPERT_ASSESSMENT);
    onExpertAssessmentChanged(view->getExpertAssessment());

    connect(view, &AddUserView::saveUserButtonClicked,
            this, &AddUserController::onSaveUserButtonClicked);
}

//  :: Serivce ::
AddUserService *AddUserController::getService() const {
    return m_service;
}
void AddUserController::setService(AddUserService *service) {
    m_service = service;

    connect(m_service, &AddUserService::error,
            m_view, &AddUserView::showErrorMessage);
    connect(m_service, &AddUserService::userAdded,
            m_view, &AddUserView::editingCanceled);
}

//  :: Private methods ::

void AddUserController::onLoginChanged(const QString &login) const {
    if(login.isEmpty()) {
        getView()->setSaveButtonEnabled(false);
        getView()->setSaveButtonToolTip(LOGIN_IS_REQUIRED_TOOL_TIP);
    } else {
        getView()->setSaveButtonEnabled(true);
        getView()->setSaveButtonToolTip(QString());
    }
}

void AddUserController::onPasswordChanged(const QString &password) const {
    auto status = PasswordsHintStatus::Hidden;
    QString repeatPassword = getView()->getRepeatPassword();

    if (!repeatPassword.isEmpty()) {
        if (password == repeatPassword) {
            status = PasswordsHintStatus::Match;
        } else {
            status = PasswordsHintStatus::NotMatch;
        }
    }

    getView()->setPasswordsHintStatus(status);
}

void AddUserController::onRepeatPasswordChanged(const QString &repeatPassword) const {
    auto status = PasswordsHintStatus::Hidden;
    QString password = getView()->getPassword();

    if (!password.isEmpty() && repeatPassword.size() >= password.size()) {
        if (password == repeatPassword) {
            status = PasswordsHintStatus::Match;
        } else {
            status = PasswordsHintStatus::NotMatch;
        }
    }

    getView()->setPasswordsHintStatus(status);
}

void AddUserController::onExpertAssessmentChanged(int assessement) {
    getView()->setUserExcludedFromAsstimationMessageVisibility(
                assessement == MINIMUM_EXPERT_ASSESSMENT
                );
}

void AddUserController::onSaveUserButtonClicked() const {
    QString password = getView()->getPassword();
    QString repeatPassword = getView()->getRepeatPassword();
    if(password.isEmpty() && repeatPassword.isEmpty()) {
        addUser();
    } else if (password == repeatPassword) {
        addUser();
    } else {
        getView()->setPasswordsHintStatus(PasswordsHintStatus::NotMatch);
    }
}

void AddUserController::addUser() const {
    User user;
    user.setLogin(getView()->getLogin());
    user.setPassword(getView()->getPassword());
    user.setRole(getView()->getRole());
}
