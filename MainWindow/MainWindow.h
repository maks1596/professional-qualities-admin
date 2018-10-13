#pragma once

#include <QMainWindow>
#include "Navigation/INavigation.h"

#include "Entities/Test/Test.h"

namespace Ui {
class MainWindow;
}

class User;
class PassedTest;
class ScaleStatistics;

class MainWindow : public QMainWindow,
                   public INavigation {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    //  :: INavigation interface ::
    void push(QWidget *widget) override;
    void pop() override;

signals:
    void aboutToClose();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onUsersBtnClicked();
    void onTestsBtnClicked();
    void onStatisticsButtonClicled();
    void onBackToMainMenu();

    void pushAddUserViewToStack();
    void pushEditUserViewToStack(const User &user);
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
    template<class T>
    T *currentWidget();

	void clearStatusBar();

    Ui::MainWindow *ui;
};
