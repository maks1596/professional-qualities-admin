#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QThread>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

#include "UsersForm.h"
#include "UserForm.h"

#include "TestsForm.h"
#include "TestEditingForm.h"
#include "TestReader.h"
#include "AsyncDatabaseHelper.h"
#include "DatabaseHelper.h"

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

    connect(ui->addTestBtn, SIGNAL(clicked()),
            this, SLOT(createTestForm()));
    connect(ui->addUserBtn, SIGNAL(clicked()),
            this, SLOT(createUserForm()));
}

MainWindow::~MainWindow() {
    delete ui;
}

// ------------------- Пользователи -------------------

void MainWindow::onUsersBtnClicked() {
    UsersForm *users = new UsersForm(this);
    connect(users, &UsersForm::toMainMenuBtnClicked,
            this, &MainWindow::onBackToMainMenu);
    connect(users, SIGNAL(createUserForm(User)),
            this, SLOT(createUserForm(User)));
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
    ui->stackedWidget->setCurrentIndex(LIST_FORM);
    if(!ui->stackedWidget->currentWidget()) {
       ((UsersForm *)ui->stackedWidget->currentWidget())->update();
    } else {
        onUsersBtnClicked();
    }
}

// --------------------------- Тесты ---------------------------

void MainWindow::onTestsBtnClicked() {
    TestsForm *tests = new TestsForm(this);
    connect(tests, &TestsForm::toMainMenuBtnClicked,
            this, &MainWindow::onBackToMainMenu);
    connect(tests, &TestsForm::createTestForm,
            this, &MainWindow::createTestForm);
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
    ui->stackedWidget->setCurrentIndex(LIST_FORM);
    if(!ui->stackedWidget->currentWidget()) {
       ((TestsForm *)ui->stackedWidget->currentWidget())->update();
    } else {
        onTestsBtnClicked();
    }
}

void MainWindow::onTestRead(const Test &test) {
    popWidget();
    createTestForm(test);
}

// -------------------- Общие методы --------------------

void MainWindow::onBackToMainMenu() {
    popWidget();
    ui->stackedWidget->setCurrentIndex(MAIN_MENU);
}

void MainWindow::pushWidget(QWidget *newWidget) {
    ui->stackedWidget->addWidget(newWidget);
    ui->stackedWidget->setCurrentWidget(newWidget);
    newWidget->show();
}

void MainWindow::popWidget() {
    QWidget *curWidget = ui->stackedWidget->currentWidget();
    ui->stackedWidget->removeWidget(curWidget);
    curWidget->deleteLater();
}

void MainWindow::showStatusMessage(const QString &message) {
    ui->statusBar->showMessage(message);
}

void MainWindow::onErrorInThread(const QString &error) {
    QMessageBox::critical(this, "Ошибка", error);
}
