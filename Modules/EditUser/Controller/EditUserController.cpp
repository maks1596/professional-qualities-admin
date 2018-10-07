#include "EditUserController.h"

#include "../Service/EditUserService.h"
#include "../View/EditUserView.h"

#include "Entities/User/User.h"

//  :: Lifecycle ::
EditUserController::EditUserController(const User &user, QObject *parent)
    : QObject(parent),
      m_id(user.getId())
{ }

//  :: Public accessors ::
//  :: View ::
EditUserView *EditUserController::getView() const {
    return m_view;
}
void EditUserController::setView(EditUserView *view) {
    m_view = view;

    connect(view, &EditUserView::saveButtonClicked,
            this, &EditUserController::saveChanges);
}

//  :: Service ::
EditUserService *EditUserController::getService() const {
    return m_service;
}
void EditUserController::setService(EditUserService *service) {
    m_service = service;

    connect(m_service, &EditUserService::userUpdated,
            m_view, &EditUserView::cancelButtonClicked);
}

//  :: Private slots ::

void EditUserController::saveChanges() const {
    m_service->updateUser(User::Builder()
                          .setId(m_id)
                         .setPassword(getView()->getPassword())
                         .setRole(getView()->getRole())
                         .setName(getView()->getName())
                         .setGender(getView()->getGender())
                         .setBirthdate(getView()->getBirtdate())
                         .setProfession(getView()->getProfession())
                         .setExpertAssessment(getView()->getExpertAssessment())
                         .build());
}
