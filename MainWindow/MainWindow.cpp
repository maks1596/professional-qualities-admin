#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>

#include "Entities/User/User.h"

#include "Modules/AddUser/Assembler/AddUserAssembler.h"
#include "Modules/AddUser/View/AddUserView.h"

#include "Modules/EditUser/Assembler/EditUserAssembler.h"
#include "Modules/EditUser/View/EditUserView.h"

#include "Modules/Users/Assembler/UsersAssembler.h"

#include "Modules/TestEditing/View/TestEditingForm.h"
#include "Modules/Tests/Assembler/TestsAssembler.h"

#include "Modules/PassedTests/Assembler/PassedTestsAssembler.h"
#include "Modules/PassedTests/View/PassedTestsForm.h"

#include "Modules/PassedTest/Assembler/PassedTestAssembler.h"
#include "Modules/PassedTest/View/PassedTestForm.h"

#include "Modules/ScaleStatistics/Assembler/ScaleStatisticsAssembler.h"
#include "Modules/ScaleStatistics/View/ScaleStatisticsForm.h"

//  :: Constants ::

const int CLEAR_STATUS_BAR_TIMING = 5000;

//  :: Lifecycle  ::

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->usersBtn, &QCommandLinkButton::clicked,
            [this](){ UsersAssembler::assembly(this); });
    connect(ui->addUserBtn, &QPushButton::clicked,
            this, &MainWindow::pushAddUserViewToStack);

    connect(ui->testsBtn, &QCommandLinkButton::clicked,
            [this](){ TestsAssembler::assembly(this); });
    connect(ui->addTestBtn, SIGNAL(clicked()),
            this, SLOT(pushTestFormToStack()));

    connect(ui->statisticsButton, &QCommandLinkButton::clicked,
            this, &MainWindow::onStatisticsButtonClicled);
}

MainWindow::~MainWindow() {
    delete ui;
}

//  :: INavigation interface ::

void MainWindow::push(QWidget *widget) {
    ui->stackedWidget->addWidget(widget);
    ui->stackedWidget->setCurrentWidget(widget);
    widget->show();
    clearStatusBar();
}

void MainWindow::pop() {
    QWidget *currentWidget = ui->stackedWidget->currentWidget();
    ui->stackedWidget->removeWidget(currentWidget);
    currentWidget->deleteLater();
    clearStatusBar();
}

//  :: Protected methods ::

void MainWindow::closeEvent(QCloseEvent *event) {
    emit aboutToClose();
    QMainWindow::closeEvent(event);
}

//  :: Private slots ::
//  :: Пользователи ::

void MainWindow::pushAddUserViewToStack() {
    auto addUserView = AddUserAssembler::assembly(this);
    connect(addUserView, &AddUserView::cancelButtonClicked,
            this, &MainWindow::onCancelUserEditing);

    push(addUserView);
}

//  :: Тесты ::

void MainWindow::pushTestFormToStack(const Test &test) {
    auto ptest = new Test(test);
    auto testForm = new TestEditingForm(ptest, this);
    connect(testForm, &TestEditingForm::cancelBtnClicked,
            this, &MainWindow::onCancelTestEditing);
    connect(testForm, &TestEditingForm::testRead,
            this, &MainWindow::onTestRead);
    push(testForm);
}

//  :: Статистика ::

void MainWindow::onStatisticsButtonClicled() {
    auto passedTestsForm = PassedTestsAssembler::assembly(this);

    connect(passedTestsForm, &PassedTestsForm::backButtonClicked,
            this, &MainWindow::onBackToMainMenu);
    connect(passedTestsForm, SIGNAL(passedTestSelected(PassedTest)),
            SLOT(showTestStatisticsForm(PassedTest)));
    connect(passedTestsForm, &PassedTestsForm::error,
            this, &MainWindow::showStatusMessage);

    push(passedTestsForm);
    passedTestsForm->startUpdating();
}

void MainWindow::showTestStatisticsForm(const PassedTest &passedTest) {
    auto testStatisticsForm = PassedTestAssembler::assembly(passedTest);

    connect(testStatisticsForm, &PassedTestForm::scaleSelected,
            this, &MainWindow::showScaleStatisticsForm);
    connect(this, &MainWindow::aboutToClose,
            testStatisticsForm, &QWidget::close);
    connect(this, &MainWindow::aboutToClose,
            testStatisticsForm, &QWidget::deleteLater);

    testStatisticsForm->show();
}

void MainWindow::showScaleStatisticsForm(int testId, const ScaleStatistics &scaleStatistics) {
    auto scaleStatisticsForm = ScaleStatisticsAssembler::assembly(testId, scaleStatistics);

    connect(this, &MainWindow::destroyed,
            scaleStatisticsForm, &QWidget::close);
    connect(this, &MainWindow::aboutToClose,
            scaleStatisticsForm, &QWidget::close);
    connect(this, &MainWindow::aboutToClose,
            scaleStatisticsForm, &QWidget::deleteLater);

    scaleStatisticsForm->show();
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
    pop();
    ui->stackedWidget->setCurrentIndex(0);
}

template<class T>
T *MainWindow::currentWidget() {
    return dynamic_cast<T *>(ui->stackedWidget->currentWidget());
}

void MainWindow::clearStatusBar() {
	showStatusMessage("");
}
