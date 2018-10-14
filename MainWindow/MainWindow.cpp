#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>

#include "Entities/User/User.h"
#include "Entities/Test/Test.h"
#include "EntitesOutput/EntitiesOutput.h"

#include "Modules/AddUser/Assembler/AddUserAssembler.h"
#include "Modules/AddUser/Output/AddUserOutput.h"

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
            this, &MainWindow::showUsersView);
    connect(ui->addUserBtn, &QPushButton::clicked,
            this, &MainWindow::showAddUserView);

    connect(ui->testsBtn, &QCommandLinkButton::clicked,
            this, &MainWindow::showTestsView);
    connect(ui->addTestBtn, &QPushButton::clicked,
            this, &MainWindow::showAddTestView);

    connect(ui->statisticsButton, &QCommandLinkButton::clicked,
            this, &MainWindow::showStatisticsView);

    m_timer.setInterval(CLEAR_STATUS_BAR_TIMING);
    connect(&m_timer, &QTimer::timeout,
            this, &MainWindow::clearStatusBar);
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

void MainWindow::showUsersView() {
    QWidget *view = nullptr;
    EntitiesOutput *output = nullptr;
    std::tie(view, output) = UsersAssembler::assembly(this);

    connectEntitiesOutput(output);
    push(view);
}

void MainWindow::showAddUserView() {
    QWidget *view = nullptr;
    AddUserOutput *output = nullptr;
    std::tie(view, output) = AddUserAssembler::assembly(this);

    connect(output, &AddUserOutput::userAdded,
            this, &MainWindow::showUsersView);
    connect(output, &AddUserOutput::error,
            this, &MainWindow::showCriticalMessage);

    push(view);
}

//  :: Тесты ::

void MainWindow::showTestsView() {
    QWidget *view = nullptr;
    EntitiesOutput *output = nullptr;
    std::tie(view, output) = TestsAssembler::assembly(this);

    connectEntitiesOutput(output);
    push(view);
}

void MainWindow::showAddTestView() {
    showEditTestView(Test());
}

void MainWindow::showEditTestView(const Test &test) {
    auto ptest = new Test(test);
    auto testForm = new TestEditingForm(ptest, this);

    connect(testForm, &TestEditingForm::testRead,
            [this](const Test &test)
            { pop(); emit showEditTestView(test); });
    connect(testForm, &TestEditingForm::testReplaced,
            this, &MainWindow::showTestsView);

    push(testForm);
}

//  :: Статистика ::

void MainWindow::showStatisticsView() {
    auto passedTestsForm = PassedTestsAssembler::assembly(this);

    connect(passedTestsForm, &PassedTestsForm::backButtonClicked,
            this, &MainWindow::pop);
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

    m_timer.stop();
    m_timer.start();
}

void MainWindow::showCriticalMessage(const QString &error) {
	QMessageBox::critical(this, "Ошибка", error);
}

// :: Private methods ::

void MainWindow::clearStatusBar() {
    showStatusMessage("");
}

inline
void MainWindow::connectEntitiesOutput(EntitiesOutput *output) {
    connect(output, &EntitiesOutput::statusMessage,
            this, &MainWindow::showStatusMessage);
    connect(output, &EntitiesOutput::error,
            this, &MainWindow::showCriticalMessage);
}
