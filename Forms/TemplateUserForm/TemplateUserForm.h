#pragma once

#include <QWidget>

namespace Ui {
class TemplateUserForm;
}

class TemplateUserForm : public QWidget {
    Q_OBJECT

public:
    explicit TemplateUserForm(QWidget *parent = nullptr);
    ~TemplateUserForm();

signals:
    void saveButtonClicked();
    void cancelButtonClicked();

protected:
    QString getTitle() const;
    void setTitle(const QString &title);

    QWidget *getUserDataForm() const;
    void setUserDataForm(QWidget *userDataForm);

    QWidget *getPersonalDataForm() const;
    void setPersonalDataForm(QWidget *personalDataForm);

private:
    Ui::TemplateUserForm *ui;
};
