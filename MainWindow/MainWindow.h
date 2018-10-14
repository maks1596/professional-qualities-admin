#pragma once

#include <QMainWindow>
#include "Navigation/INavigation.h"

#include <QTimer>

namespace Ui {
class MainWindow;
}

class EntitiesOutput;
class User;
class PassedTest;
class ScaleStatistics;
class Test;

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
    void showUsersView();
    void showAddUserView();

    void showTestsView();
    void showAddTestView();
    void showEditTestView(const Test &test);

    void showStatisticsView();

    void showTestStatisticsForm(const PassedTest &passedTest);
    void showScaleStatisticsForm(int testId,
                                        const ScaleStatistics &scaleStatistics);

    void showCriticalMessage(const QString &error);
    void showStatusMessage(const QString &message);

private:
	void clearStatusBar();
    void connectEntitiesOutput(EntitiesOutput *output);

    QTimer m_timer;
    Ui::MainWindow *ui;
};
