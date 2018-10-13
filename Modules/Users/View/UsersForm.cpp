#include "UsersForm.h"

//  :: Constants ::

const QString TITLE = "Тестируемые";
const QString ADD_BUTTON_ICON_NAME = ":/images/account-plus.svg";
const QString ADD_BUTTON_TOOL_TIP = "Добавить тестируемого";

//  :: Lifecycle ::

UsersForm::UsersForm(QWidget *parent)
    : EntitiesForm(parent) { }

//  :: Public methods ::

void UsersForm::showRemoveUserDialog(uint userIndex) {
    int btn = QMessageBox::question(this, "Удаление пользователя",
                                    "Вы действительно хотите удалить пользователя?",
                                    QMessageBox::Yes, QMessageBox::No);
    if(btn == QMessageBox::Yes) {
        emit removeUser(userIndex);
    }
}

//  :: Protected methods ::

QString UsersForm::getTitle() const {
    return TITLE;
}

QString UsersForm::getAddButtonIconName() const {
    return ADD_BUTTON_ICON_NAME;
}

QString UsersForm::getAddButtonToolTip() const {
    return  ADD_BUTTON_TOOL_TIP;
}
