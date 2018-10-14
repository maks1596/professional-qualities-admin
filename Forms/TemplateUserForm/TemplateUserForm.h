#pragma once

#include "Navigation/NavigationView.h"

namespace Ui {
class TemplateUserForm;
}

class TemplateUserForm : public NavigationView {
    Q_OBJECT

public:
    explicit TemplateUserForm(QWidget *userDataWidget,
                              QWidget *personalDataWidget,
                              QWidget *parent = nullptr);
    ~TemplateUserForm() override;

    void setSaveButtonEnabled(bool enabled);
    void setSaveButtonToolTip(const QString &toolTip);

signals:
    void saveButtonClicked();
    void cancelButtonClicked();

protected:
    QString getTitle() const;
    void setTitle(const QString &title);

    QWidget *getUserDataWidget();
    QWidget *getUserDataWidget() const;

    QWidget *getPersonalDataWidget();
    QWidget *getPersonalDataWidget() const;

private:    
    QWidget *m_userDataWidget;
    QWidget *m_personalDataWidget;

    Ui::TemplateUserForm *ui;
};
