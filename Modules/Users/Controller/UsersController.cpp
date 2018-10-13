#include "UsersController.h"

#include <QModelIndex>

#include "../View/UsersForm.h"

//  :: Lifecycle ::

UsersController::UsersController(QObject *parent)
    : QObject(parent) { }

//  :: Public accessors ::
//  :: View ::
UsersForm *UsersController::getView() const {
    return m_view;
}
void UsersController::setView(UsersForm *view) {
    m_view = view;

    connect(view, &UsersForm::entityClicked,
            this, &UsersController::onUserClicked);
    connect(view, &UsersForm::entityDoubleClicked,
            this, &UsersController::onUserDoubleClicked);

    connect(view, &UsersForm::addButtonClicked,
            view, &UsersForm::showAddUserView);
    connect(view, &UsersForm::removeUserClicked,
            this, &UsersController::onRemoveUserClicked);
}

//  :: Model ::
UsersModel *UsersController::getModel() const {
    return m_model;
}
void UsersController::setModel(UsersModel *model) {
    m_model = model;
}

//  :: Service ::
UsersService *UsersController::getService() const {
    return m_service;
}
void UsersController::setService(UsersService *service) {
    m_service = service;
}

//  :: Private methods ::

void UsersController::onUserClicked(const QModelIndex &idx) {
    if (idx.isValid()) {
        if (idx.column() == m_model->removeColumnIndex()) {
            m_view->showRemoveUserDialog(idx.row());
        }
    }
}

void UsersController::onUserDoubleClicked(const QModelIndex &idx) {
    if (idx.isValid()) {
        auto userIndex = idx.row();
        if (idx.column() == m_model->removeColumnIndex()) {
            m_view->showRemoveUserDialog(userIndex);
        } else {
            m_view->showEditUserView(m_model->getUser(userIndex));
        }
    }
}

void UsersController::onRemoveUserClicked(uint index) {
    m_service->removeUser(m_model->getUserId(index));
}
