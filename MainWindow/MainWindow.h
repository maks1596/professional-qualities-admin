#pragma once

#include <QMainWindow>

#include "Entities/Test/Test.h"

namespace Ui {
class MainWindow;
}

class User;
class PassedTest;
class ScaleStatistics;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void aboutToClose();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void onUsersBtnClicked();
    void onTestsBtnClicked();
    void onStatisticsButtonClicled();
    void onBackToMainMenu();

    void pushAddUserFormToStack();
    void pushEditUserFormToStack(const User &user);
    void onCancelUserEditing();

    void pushTestFormToStack(const Test &test = Test());
    void onCancelTestEditing();
    void onTestRead(const Test &test);

    void showTestStatisticsForm(const PassedTest &passedTest);
    void showScaleStatisticsForm(int testId,
                                        const ScaleStatistics &scaleStatistics);

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
