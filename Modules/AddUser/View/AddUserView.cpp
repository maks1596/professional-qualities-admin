#include "AddUserView.h"

#include <QDate>

#include "Entities/Gender/Gender.h"

#include "Forms/PersonalDataForm/PersonalDataForm.h"
#include "Forms/UserDataForm/UserDataForm.h"

//  :: Constants ::

const QString TITLE = "Создание учётной записи";

//  :: Lifecycle ::

AddUserView::AddUserView(QWidget *parent) :
    TemplateUserForm(new UserDataForm,
                     new PersonalDataForm,
                     parent)
{
    setTitle(TITLE);
    initUserDataForm();
    initPersonalDataForm();
}

//  :: Public accessors ::
//  :: Login ::
QString AddUserView::getLogin() const {
    return getUserDataForm()->getLogin();
}

//  :: Password ::
QString AddUserView::getPassword() const {
    return getUserDataForm()->getPassword();
}

//  :: Repeat password ::
QString AddUserView::getRepeatPassword() const {
    return getUserDataForm()->getRepeatPassword();
}

//  :: Role ::
UserRole AddUserView::getRole() const {
    return getUserDataForm()->getRole();
}

//  :: Name ::
QString AddUserView::getName() const {
    return getPersonalDataForm()->getName();
}

//  :: Gender ::
Gender AddUserView::getGender() const {
    return getPersonalDataForm()->getGender();
}

//  :: Birtdate ::
QDate AddUserView::getBirthdate() const {
    return getPersonalDataForm()->getBirthdate();
}

//  :: Profession ::
QString AddUserView::getProfession() const {
    return getPersonalDataForm()->getProfession();
}

//  :: Expert assessment ::
int AddUserView::getExpertAssessment() const {
    return getPersonalDataForm()->getExpertAssessment();
}

//  :: Passwords hint ::
void AddUserView::setPasswordsHintStatus(PasswordsHintStatus status) {
    getUserDataForm()->setPasswordsHintStatus(status);
}

//  :: Birthdate range ::
void AddUserView::setMaximumBirtdate(const QDate &maxDate) {
    getPersonalDataForm()->setMaximumBirtdate(maxDate);
}
void AddUserView::setMinimumBirtdate(const QDate &minDate) {
    getPersonalDataForm()->setMinimumBirtdate(minDate);
}

//  :: Expert assessment range ::
void AddUserView::setMaximumExpertAssessment(int maxAssessment) {
    getPersonalDataForm()->setMaximumExpertAssessment(maxAssessment);
}
void AddUserView::setMinimumExpertAssessment(int minAssessment) {
    getPersonalDataForm()->setMinimumExpertAssessment(minAssessment);
}

//  :: Professions model ::
QStringList AddUserView::getProfessions() const {
    return getPersonalDataForm()->getProfessions();
}
void AddUserView::setProfessions(const QStringList &professions) {
    getPersonalDataForm()->setProfessions(professions);
}

void AddUserView::setUserExcludedFromAsstimationMessageVisibility(bool visible) {
    getPersonalDataForm()
            ->setUserExcludedFromAsstimationMessageVisibility(visible);
}

//  :: Private methods ::

inline
void AddUserView::initUserDataForm() {
    connect(getUserDataForm(), &UserDataForm::loginChanged,
            this, &AddUserView::loginChanged);
    connect(getUserDataForm(), &UserDataForm::passwordChanged,
            this, &AddUserView::passwordChanged);
    connect(getUserDataForm(), &UserDataForm::repeatPasswordChanged,
            this, &AddUserView::repeatPasswordChanged);
}

inline
void AddUserView::initPersonalDataForm() {
    connect(getPersonalDataForm(), &PersonalDataForm::expertAssessmentChanged,
            this, &AddUserView::expertAssessmentChanged);
}

inline
UserDataForm *AddUserView::getUserDataForm() const {
    return dynamic_cast<UserDataForm *>(getUserDataWidget());
}

inline
PersonalDataForm *AddUserView::getPersonalDataForm() const {
    return dynamic_cast<PersonalDataForm *>(getPersonalDataWidget());
}
