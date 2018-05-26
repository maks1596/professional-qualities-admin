#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include "Modules/Users/View/UsersForm.h"
#include "Forms/UserForm/UserForm.h"

#include "Modules/Tests/View/TestsForm.h"
#include "Modules/TestEditing/View/TestEditingForm.h"

//  :: Constants ::

const int CLEAR_STATUS_BAR_TIMING = 5000;

//  :: Lifecycle  ::

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(MAIN_MENU);

    connect(ui->usersBtn, &QCommandLinkButton::clicked,
            this, &MainWindow::onUsersBtnClicked);
    connect(ui->testsBtn, &QCommandLinkButton::clicked,
            this, &MainWindow::onTestsBtnClicked);
    connect(ui->statisticsButton, &QCommandLinkButton::clicked,
            this, &MainWindow::onStatisticsButtonClicled);

    connect(ui->addTestBtn, SIGNAL(clicked()),
            this, SLOT(createTestForm()));
    connect(ui->addUserBtn, SIGNAL(clicked()),
            this, SLOT(createUserForm()));
}

MainWindow::~MainWindow() {
    delete ui;
}

//  :: Пользователи ::

void MainWindow::onUsersBtnClicked() {
    UsersForm *users = new UsersForm(this);
    connect(users, &UsersForm::toMainMenuBtnClicked,
            this, &MainWindow::onBackToMainMenu);
    connect(users, SIGNAL(createUserForm(User)),
            this, SLOT(createUserForm(User)));
	connect(users, &TestsForm::error,
			this, &MainWindow::showStatusMessage);
    pushWidget(users);
}

void MainWindow::createUserForm(const User &user) {
    UserForm *userForm = new UserForm(user, this);
    connect(userForm, &UserForm::editingCanceled,
            this, &MainWindow::onCancelUserEditing);
    pushWidget(userForm);
}

void MainWindow::onCancelUserEditing() {
    popWidget();
    ui->stackedWidget->setCurrentIndex(ENTITIES_FORM);
    if(!ui->stackedWidget->currentWidget()) {
	   ((UsersForm *)ui->stackedWidget->currentWidget())->startUpdating();
    } else {
        onUsersBtnClicked();
    }
}

//  :: Тесты ::

void MainWindow::onTestsBtnClicked() {
    TestsForm *tests = new TestsForm(this);
    connect(tests, &TestsForm::toMainMenuBtnClicked,
            this, &MainWindow::onBackToMainMenu);
    connect(tests, &TestsForm::createTestForm,
            this, &MainWindow::createTestForm);
	connect(tests, &TestsForm::error,
			this, &MainWindow::showStatusMessage);
    pushWidget(tests);
}

void MainWindow::createTestForm(const Test &test) {
    Test *ptest = new Test(test);
    TestEditingForm *testForm = new TestEditingForm(ptest, this);
    connect(testForm, &TestEditingForm::cancelBtnClicked,
            this, &MainWindow::onCancelTestEditing);
    connect(testForm, &TestEditingForm::testRead,
            this, &MainWindow::onTestRead);
    pushWidget(testForm);
}

void MainWindow::onCancelTestEditing() {
    popWidget();
    ui->stackedWidget->setCurrentIndex(ENTITIES_FORM);
    if(!ui->stackedWidget->currentWidget()) {
	   ((TestsForm *)ui->stackedWidget->currentWidget())->startUpdating();
    } else {
        onTestsBtnClicked();
    }
}

void MainWindow::onTestRead(const Test &test) {
    popWidget();
    createTestForm(test);
}

//  :: Статистика ::

void MainWindow::onStatisticsButtonClicled()
{
    showStatusMessage("Нажата кнопка \"Статистика\"");
}

//  :: Private slots ::

void MainWindow::showStatusMessage(const QString &message) {
	ui->statusBar->showMessage(message);
	QTimer::singleShot(CLEAR_STATUS_BAR_TIMING,
					   this , &MainWindow::clearStatusBar);
}

void MainWindow::showCriticalMessage(const QString &error) {
	QMessageBox::critical(this, "Ошибка", error);
}

// :: Private methods ::

void MainWindow::onBackToMainMenu() {
    popWidget();
    ui->stackedWidget->setCurrentIndex(MAIN_MENU);
}

void MainWindow::pushWidget(QWidget *newWidget) {
    ui->stackedWidget->addWidget(newWidget);
    ui->stackedWidget->setCurrentWidget(newWidget);
    newWidget->show();
	clearStatusBar();
}

void MainWindow::popWidget() {
    QWidget *curWidget = ui->stackedWidget->currentWidget();
    ui->stackedWidget->removeWidget(curWidget);
    curWidget->deleteLater();
	clearStatusBar();
}

void MainWindow::clearStatusBar() {
	showStatusMessage("");
}
