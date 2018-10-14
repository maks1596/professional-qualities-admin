#pragma once

#include "Forms/EntitiesForm/EntitiesForm.h"

class Test;

class TestsForm : public EntitiesForm {
Q_OBJECT

public:
    explicit TestsForm(QWidget *parent = nullptr);

    void showRemoveTestDialog(uint testIndex);
    void showEditTestView(const Test &test);
    void showAddTestView() const;
    void showTestIsUsedMessage();

signals:
    void removeTestClicked(uint testIndex);

protected:
    QString getTitle() const override;
    QString getAddButtonIconName() const override;
    QString getAddButtonToolTip() const override;
};
