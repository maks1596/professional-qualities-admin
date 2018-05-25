#pragma once

#include "Forms/EntitiesForm/EntitiesForm.h"

class ShortTestInfo;
class Test;
class TestsModel;

class TestsForm : public EntitiesForm {
Q_OBJECT

public:
    explicit TestsForm(QWidget *parent = nullptr);

public slots:
	virtual void update() override;

signals:
    void createTestForm(const Test &test);

protected slots:
	virtual void onAddBtnClicked() override;

protected:
	virtual void removeEntity(const int &testId) override;
	virtual void editEntity(const int &testId) override;

private slots:
	void updateTestsTable(const QList<ShortTestInfo> &tests);
	void showTestIsUsedMessage();

private:
	void initModel();

	TestsModel *m_model;
};
