#include "UsersForm.h"

#include <QMessageBox>

#include "Modules/AddUser/Assembler/AddUserAssembler.h"
#include "Modules/AddUser/Output/AddUserOutput.h"

#include "Modules/EditUser/Assembler/EditUserAssembler.h"
#include "Modules/EditUser/Output/EditUserOutput.h"

//  :: Constants ::

const QString TITLE = "Тестируемые";
const QString ADD_BUTTON_ICON_NAME = ":/images/account-plus.svg";
const QString ADD_BUTTON_TOOL_TIP = "Добавить тестируемого";

//  :: Lifecycle ::

UsersForm::UsersForm(QWidget *parent)
    : EntitiesForm(TITLE,
                   ADD_BUTTON_ICON_NAME,
                   ADD_BUTTON_TOOL_TIP,
                   parent) { }

//  :: Public methods ::

void UsersForm::showRemoveUserDialog(uint userIndex) {
    int btn = QMessageBox::question(this, "Удаление пользователя",
                                    "Вы действительно хотите удалить пользователя?",
                                    QMessageBox::Yes, QMessageBox::No);
    if(btn == QMessageBox::Yes) {
        emit removeUserClicked(userIndex);
    }
}

void UsersForm::showEditUserView(const User &user) {
    QWidget *view = nullptr;
    EditUserOutput *output = nullptr;
    std::tie(view, output) = EditUserAssembler::assembly(user, this);

    connect(output, &EditUserOutput::error,
            this, &UsersForm::error);
    push(view);
}

void UsersForm::showAddUserView() {
    QWidget *view = nullptr;
    AddUserOutput *output = nullptr;
    std::tie(view, output) = AddUserAssembler::assembly(this);

    connect(output, &AddUserOutput::error,
            this, &UsersForm::error);
    push(view);
}
