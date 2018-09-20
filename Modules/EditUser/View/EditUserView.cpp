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
    personalDataForm->setBirthdate(user.getBirthday());
    personalDataForm->setProfession(user.getProfession());
    personalDataForm->setExpertAssessment(user.getExpertAssessment());
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
