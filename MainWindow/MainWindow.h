#pragma once

#include <QMainWindow>

#include "Entities/User/User.h"
#include "Entities/Test/Test.h"

namespace Ui {
class MainWindow;
}

class PassedTest;
class ScaleStatistics;

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onUsersBtnClicked();
    void onTestsBtnClicked();
    void onStatisticsButtonClicled();
    void onBackToMainMenu();

    void pushUserFormToStack(const User &user = User());
    void onCancelUserEditing();

    void pushTestFormToStack(const Test &test = Test());
    void onCancelTestEditing();
    void onTestRead(const Test &test);

    void pushTestStatisticsFormToStack(const PassedTest &passedTest);
    void pushScaleStatisticsFormToStack(const ScaleStatistics &scaleStatistics);

    void showCriticalMessage(const QString &error);
    void showStatusMessage(const QString &message);

private:
    void pushWidget(QWidget *newWidget);
    void popWidget();
    template<class T>
    T *currentWidget();

	void clearStatusBar();

    Ui::MainWindow *ui;
};
