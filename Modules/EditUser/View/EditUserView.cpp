#include "EditUserView.h"

#include "Forms/EditUserDataForm/EditUserDataForm.h"
#include "Forms/PersonalDataForm/PersonalDataForm.h"

//  :: Lifecycle ::

EditUserView::EditUserView(const User &user, QWidget *parent) :
    TemplateUserForm(new EditUserDataForm,
                     new PersonalDataForm,
                     parent)
{

}
