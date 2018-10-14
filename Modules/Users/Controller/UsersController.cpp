#include "UsersController.h"

#include <QModelIndex>

#include "../View/UsersForm.h"
#include "../Service/UsersService.h"
#include "../Model/UsersModel.h"

#include "Entities/User/User.h"

//  :: Constants ::

const int UPDATE_TIMING = 5000;

//  :: Lifecycle ::

UsersController::UsersController(UsersForm *view,
                                 UsersModel *model,
                                 UsersService *service)
    : EntitiesOutput(view),
      m_view(view),
      m_model(model),
      m_service(service)
{
    connectView();
    connectService();

    m_timer.setInterval(UPDATE_TIMING);
    connect(&m_timer, &QTimer::timeout,
            m_service, &UsersService::getUsers);
    m_timer.start();

    m_service->getUsers();
}

//  :: Private slots ::

void UsersController::onUserClicked(const QModelIndex &idx) {
    if (idx.isValid()) {
        if (idx.column() == m_model->getRemoveColumnIndex()) {
            m_view->showRemoveUserDialog(idx.row());
        }
    }
}

void UsersController::onUserDoubleClicked(const QModelIndex &idx) {
    if (idx.isValid()) {
        auto userIndex = idx.row();
        if (idx.column() == m_model->getRemoveColumnIndex()) {
            m_view->showRemoveUserDialog(userIndex);
        } else {
            m_view->showEditUserView(m_model->getUser(userIndex));
        }
    }
}

void UsersController::onRemoveUserClicked(uint index) {
    m_service->removeUser(m_model->getUserId(index));
}

//  :: Private methods ::

void UsersController::connectView() {
    connect(m_view, &UsersForm::entityClicked,
            this, &UsersController::onUserClicked);
    connect(m_view, &UsersForm::entityDoubleClicked,
            this, &UsersController::onUserDoubleClicked);

    connect(m_view, &UsersForm::addButtonClicked,
            m_view, &UsersForm::showAddUserView);
    connect(m_view, &UsersForm::removeUserClicked,
            this, &UsersController::onRemoveUserClicked);

    connect(m_view, &UsersForm::backButtonClicked,
            m_view, &UsersForm::pop);
    connect(m_view, &UsersForm::error,
            this, &UsersController::error);
}

void UsersController::connectService() {
    connect(m_service, &UsersService::usersGot,
            m_model, &UsersModel::setUsers);
    connect(m_service, &UsersService::error,
            this, &UsersController::statusMessage);
}
