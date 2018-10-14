#include "TestsForm.h"

#include <QMessageBox>

#include "Entities/Test/Test.h"
#include "Modules/TestEditing/View/TestEditingForm.h"

//  :: Constatns ::

const QString TITLE = "Тесты";
const QString ADD_BUTTON_ICON_NAME = ":/images/file-plus.svg";
const QString ADD_BUTTON_TOOL_TIP = "Добавить тест";
const QString TEST_IS_USED_MESSAGE = "Удаление теста невозможно\n"
									 "Тест уже был пройден";

//  :: Lifecycle ::

TestsForm::TestsForm(QWidget *parent) :
    EntitiesForm(TITLE,
                 ADD_BUTTON_ICON_NAME,
                 ADD_BUTTON_TOOL_TIP,
                 parent) { }

//  :: Public methods ::

void TestsForm::showRemoveTestDialog(uint testIndex) {
    int btn = QMessageBox::question(this, "Удаление пользователя",
                                    "Вы действительно хотите удалить пользователя?",
                                    QMessageBox::Yes, QMessageBox::No);
    if(btn == QMessageBox::Yes) {
        emit removeTestClicked(testIndex);
    }
}

void TestsForm::showEditTestView(const Test &test) {
    auto view = new TestEditingForm(new Test(test), this);
    connect(view, &TestEditingForm::error,
            this, &TestsForm::error);
    connect(view, &TestEditingForm::testRead,
            [this](const Test &test)
            { pop(); emit showEditTestView(test); });
    push(view);
}

void TestsForm::showAddTestView() {
    showEditTestView(Test());
}

void TestsForm::showTestIsUsedMessage() {
    emit error(TEST_IS_USED_MESSAGE);
}
