#pragma once

#include <QWidget>

namespace Ui {
class TemplateUserForm;
}

class TemplateUserForm : public QWidget {
    Q_OBJECT

public:
    explicit TemplateUserForm(QWidget *userDataWidget,
                              QWidget *personalDataWidget,
                              QWidget *parent = nullptr);
    ~TemplateUserForm();

    void setSaveButtonEnabled(bool enabled);
    void setSaveButtonToolTip(const QString &toolTip);

    void showErrorMessageBox(const QString &message);

signals:
    void saveButtonClicked();
    void cancelButtonClicked();

protected:
    QString getTitle() const;
    void setTitle(const QString &title);

    QWidget *getUserDataWidget() const;
    QWidget *getPersonalDataWidget() const;

private:    
    QWidget *m_userDataWidget;
    QWidget *m_personalDataWidget;

    Ui::TemplateUserForm *ui;
};
