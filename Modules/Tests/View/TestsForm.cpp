#include "TestsForm.h"

#include <QMessageBox>

//  :: Constatns ::

const QString TITLE = "Тесты";
const QString ADD_BUTTON_ICON_NAME = ":/images/file-plus.svg";
const QString ADD_BUTTON_TOOL_TIP = "Добавить тест";
const QString TEST_IS_USED_MESSAGE = "Удаление теста невозможно\n"
									 "Тест уже был пройден";

//  :: Lifecycle ::

TestsForm::TestsForm(QWidget *parent) :
    EntitiesForm(parent) { }

//  :: Public methods ::

void TestsForm::showRemoveTestDialog(uint testIndex) {
    int btn = QMessageBox::question(this, "Удаление пользователя",
                                    "Вы действительно хотите удалить пользователя?",
                                    QMessageBox::Yes, QMessageBox::No);
    if(btn == QMessageBox::Yes) {
        emit removeTestClicked(testIndex);
    }
}

void TestsForm::showEditTestView(const Test &test)
{

}

void TestsForm::showAddTestView() const
{

}

void TestsForm::showTestIsUsedMessage() {
    showCriticalMessage(TEST_IS_USED_MESSAGE);
}

//  :: Protected methods ::

QString TestsForm::getTitle() const {
    return TITLE;
}

QString TestsForm::getAddButtonIconName() const {
    return ADD_BUTTON_ICON_NAME;
}

QString TestsForm::getAddButtonToolTip() const {
    return  ADD_BUTTON_TOOL_TIP;
}
