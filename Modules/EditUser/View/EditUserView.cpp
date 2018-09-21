#include "EditUserView.h"

#include <QDate>

#include "Entities/User/User.h"

#include "Forms/EditUserDataForm/EditUserDataForm.h"
#include "Forms/PersonalDataForm/PersonalDataForm.h"

//  :: Constants ::

const QString TITLE = "Редактирование данных пользователя";

//  :: Lifecycle ::

EditUserView::EditUserView(const User &user, QWidget *parent) :
    TemplateUserForm(new EditUserDataForm,
                     new PersonalDataForm,
                     parent)
{
    setTitle(TITLE);

    auto userDataForm = getEditUserDataForm();
    userDataForm->setLogin(user.getLogin());
    userDataForm->setPassword(user.getPassword());
    userDataForm->setRole(user.getRole());

    auto personalDataForm = getPersonalDataForm();
    personalDataForm->setName(user.getName());
    personalDataForm->setGender(user.getGender());
    personalDataForm->setBirthdate(user.getBirthdate());
    personalDataForm->setProfession(user.getProfession());
    personalDataForm->setExpertAssessment(user.getExpertAssessment());
}

//  :: Public accessors ::
//  :: Edit user data form
QString EditUserView::getLogin() const {
    return getEditUserDataForm()->getLogin();
}
QString EditUserView::getPassword() const {
    return getEditUserDataForm()->getPassword();
}
UserRole EditUserView::getRole() const {
    return getEditUserDataForm()->getRole();
}

//  :: Personal data form
QString EditUserView::getName() const {
    return getPersonalDataForm()->getName();
}
Gender EditUserView::getGender() const {
    return getPersonalDataForm()->getGender();
}
QDate EditUserView::getBirtdate() const {
    return getPersonalDataForm()->getBirthdate();
}
QString EditUserView::getProfession() const {
    return getPersonalDataForm()->getProfession();
}

int EditUserView::getExpertAssessment() const {
    return getPersonalDataForm()->getExpertAssessment();
}

//  :: Private methods ::

inline
EditUserDataForm *EditUserView::getEditUserDataForm() {
    return static_cast<EditUserDataForm *>(getUserDataWidget());
}
inline
EditUserDataForm *EditUserView::getEditUserDataForm() const {
    return static_cast<EditUserDataForm *>(getUserDataWidget());
}

inline
PersonalDataForm *EditUserView::getPersonalDataForm() {
    return static_cast<PersonalDataForm *>(getPersonalDataWidget());
}
inline
PersonalDataForm *EditUserView::getPersonalDataForm() const {
    return static_cast<PersonalDataForm *>(getPersonalDataWidget());
}
