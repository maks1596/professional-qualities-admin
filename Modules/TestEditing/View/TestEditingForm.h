#pragma once

#include <QWidget>

class ScalesContainer;
class ShortTestInfo;
class Test;
class TestEditingModel;
class TestMainForm;

namespace Ui {
class TestEditingForm;
}

class TestEditingForm : public QWidget {
Q_OBJECT

public:
    explicit TestEditingForm(Test *test, QWidget *parent = nullptr);
    ~TestEditingForm();

signals:
    void cancelBtnClicked();
    void testRead(const Test &test);

private slots:
    void onSaveTestBtnClicked();
    void onLoadFromFileClicked();
	void showReplaceTestDialog(const ShortTestInfo &shortTestInfo);
	void showTestIsUsedMessage();

	void showCriticalMessage(const QString &error);

private:
	void initModel();
	void replaceTest();
    void putTest();

    Test *m_test;
	TestEditingModel *m_model;
    TestMainForm *m_testMainForm;
    ScalesContainer *m_scalesContainer;
    Ui::TestEditingForm *ui;
};
