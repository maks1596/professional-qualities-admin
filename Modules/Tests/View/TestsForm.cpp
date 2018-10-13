#include "TestsForm.h"

#include <QMessageBox>

#include "Entities/ShortTestInfo/ShortTestInfo.h"
#include "Entities/Test/Test.h"
#include "../Model/TestsModel.h"

//  :: Constatns ::

const QStringList kHeaderLabels {
    "Название теста"
};

const QString TITLE = "Тесты";
const QString ADD_BUTTON_ICON_NAME = ":/images/file-plus.svg";
const QString ADD_BUTTON_TOOL_TIP = "Добавить тест";
const QString TEST_IS_USED_MESSAGE = "Удаление теста невозможно\n"
									 "Тест уже был пройден";

//  :: Lifecycle ::

TestsForm::TestsForm(QWidget *parent) :
	EntitiesForm(parent)
{
    setTitle(TITLE);
    setAddButtonIcon(ADD_BUTTON_ICON_NAME);
    setAddButtonToolTip(ADD_BUTTON_TOOL_TIP);
    setHeaderLabels(kHeaderLabels);
	initModel();
}

//  :: Abstract methods ::

void TestsForm::update() {
	m_model->getTests();
}

//  :: Protected slots ::

void TestsForm::onAddBtnClicked() {
	emit createTestForm(Test());
}

void TestsForm::editEntity(const int &testId) {
	m_model->getTest(testId);
}

void TestsForm::removeEntity(const int &testId) {
    int btn = QMessageBox::question(this, "Удаление тест",
                                    "Вы действительно хотите удалить тест?",
                                    QMessageBox::Yes, QMessageBox::No);
    if(btn == QMessageBox::Yes) {
		m_model->deleteTest(testId);
    }
}

//  :: Private slots ::

void TestsForm::updateTestsTable(const QList<ShortTestInfo> &tests) {
	QList<Entity> entities;
	QList<QStringList> content;

	for (const auto &test : tests) {
		content.append({test.getName()});
		entities.append(test);
	}

	setContent(content);
	setEntities(entities);
}

void TestsForm::showTestIsUsedMessage() {
	showCriticalMessage(TEST_IS_USED_MESSAGE);
}

//  :: Private methods ::

void TestsForm::initModel() {
	m_model = new TestsModel(this);
	connect(m_model, &TestsModel::testsGot,
			this, &TestsForm::updateTestsTable);
	connect(m_model, &TestsModel::testGot,
			this, &TestsForm::createTestForm);
	connect(m_model, &TestsModel::testIsUsed,
			this, &TestsForm::showTestIsUsedMessage);
	connect(m_model, &TestsModel::error,
			this, &TestsForm::error);
}
