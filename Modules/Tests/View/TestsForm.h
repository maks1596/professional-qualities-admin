#pragma once

#include "Forms/EntitiesForm/EntitiesForm.h"

class Test;

class TestsForm : public EntitiesForm {
Q_OBJECT

public:
    explicit TestsForm(QWidget *parent = nullptr);

    void showRemoveTestDialog(uint testIndex);
    void showEditTestView(const Test &test);
    void showAddTestView();
    void showTestIsUsedMessage();

signals:
    void removeTestClicked(uint testIndex);
    void error(const QString &errorMessage);
};
