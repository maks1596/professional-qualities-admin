#pragma once

#include "Navigation/NavigationView.h"

class ScalesContainer;
class ShortTestInfo;
class Test;
class TestEditingModel;
class TestMainForm;

namespace Ui {
class TestEditingForm;
}

class TestEditingForm : public NavigationView {
    Q_OBJECT

public:
    explicit TestEditingForm(Test *test, QWidget *parent = nullptr);
    ~TestEditingForm() override;

signals:
    void testAdded();
    void testReplaced();
    void testRead(const Test &test);
    void error(const QString &errorMessage);

private slots:
    void onSaveTestBtnClicked();
    void onLoadFromFileClicked();
	void showReplaceTestDialog(const ShortTestInfo &shortTestInfo);
	void showTestIsUsedMessage();


private:
	void initModel();
	void replaceTest();
    void putTest();

    Test *m_test = nullptr;
    TestEditingModel *m_model = nullptr;
    TestMainForm *m_testMainForm = nullptr;
    ScalesContainer *m_scalesContainer = nullptr;
    Ui::TestEditingForm *ui;
};
