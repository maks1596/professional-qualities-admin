#include "TestEditingForm.h"
#include "ui_TestEditingForm.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QThread>

#include "Entities/ShortTestInfo/ShortTestInfo.h"
#include "Forms/ScalesContainer/ScalesContainer.h"
#include "Forms/TestMainForm/TestMainForm.h"
#include "Modules/TestEditing/Model/TestEditingModel.h"
#include "TestReader/TestReader.h"

//  :: Lifecycle ::

TestEditingForm::TestEditingForm(Test *test, QWidget *parent) :
    NavigationView(parent),
    m_test(test),
    m_testMainForm(new TestMainForm(test, this)),
    m_scalesContainer(new ScalesContainer(test, this)),
    ui(new Ui::TestEditingForm)
{
    ui->setupUi(this);

    ui->tabs->setCurrentIndex(0);
    ui->mainTab->layout()->addWidget(m_testMainForm);
    ui->keyTab->layout()->addWidget(m_scalesContainer);

    connect(ui->saveBtn, &QPushButton::clicked,
            this, &TestEditingForm::onSaveTestBtnClicked);
    connect(ui->cancelBtn, &QPushButton::clicked,
            this, &TestEditingForm::pop);
    connect(ui->loadFromFileBtn, &QPushButton::clicked,
            this, &TestEditingForm::onLoadFromFileClicked);

    if(m_test->getAnswerOptionsType() == UNDEFINED) {
        m_test->setAnswerOptionsType(GENERAL);
        m_testMainForm->setAnswerOptionsTypeEditable(true);
        ui->title->setText("Создание теста");
    } else {
        m_testMainForm->setAnswerOptionsTypeEditable(false);
        ui->title->setText("Редактирование теста");
    }

	initModel();
}

TestEditingForm::~TestEditingForm() {
    delete ui;
    delete m_test;
}

//  :: Private methods ::

void TestEditingForm::initModel() {
	m_model = new TestEditingModel(this);

	connect(m_model, &TestEditingModel::error,
            this, &TestEditingForm::error);

	connect(m_model, &TestEditingModel::testNameIsFree,
			this, &TestEditingForm::putTest);
	connect(m_model, &TestEditingModel::testPut,
            [this](){ pop(); emit testAdded(); });

	connect(m_model, &TestEditingModel::testNameAlreadyTaken,
			this, &TestEditingForm::showReplaceTestDialog);
	connect(m_model, &TestEditingModel::testReplaced,
            [this](){ pop(); emit testReplaced(); });
	connect(m_model, &TestEditingModel::testIsUsed,
			this, &TestEditingForm::showTestIsUsedMessage);
}

void TestEditingForm::replaceTest() {
	m_model->replaceTest(*m_test);
}

void TestEditingForm::putTest() {
	m_model->putTest(*m_test);
}

//  :: Private slots ::

void TestEditingForm::onSaveTestBtnClicked() {
	m_model->checkTestName(m_test->getName());
}

void TestEditingForm::onLoadFromFileClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Выбор файла с тестом",
                                                    "", "*.txt *.tst");
    if(fileName.isEmpty()) { return; }

    auto thread = new QThread();
    auto testReader = new TestReader();
    testReader->moveToThread(thread);

    connect(thread, &QThread::started,
            [=]{ testReader->readTest(fileName); });

    connect(testReader, &TestReader::testRead,
            this, &TestEditingForm::testRead);
    connect(testReader, &TestReader::error,
            this, &TestEditingForm::error);

    connect(testReader, &TestReader::testRead,
            thread, &QThread::quit);
    connect(testReader, &TestReader::error,
            thread, &QThread::quit);

    connect(thread, &QThread::finished,
            testReader, &TestReader::deleteLater);
    connect(thread, &QThread::finished,
            thread, &QThread::deleteLater);

    thread->start();
}

void TestEditingForm::showReplaceTestDialog(const ShortTestInfo &shortTestInfo) {
	int btn = QMessageBox::warning(this, "Тест уже существует",
								   "Тест с таким именем уже существует\n"
								   "Хотите его заменить?",
								   QMessageBox::Yes, QMessageBox::No);
	if(btn == QMessageBox::Yes) {
		m_test->setId(shortTestInfo.getId());
		replaceTest();
	}
}

void TestEditingForm::showTestIsUsedMessage() {
	QMessageBox::warning(this, "Тест уже используется",
						 "Данный тест уже используется\n"
						 "Замена теста невозможна");
}
