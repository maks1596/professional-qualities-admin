#pragma once

#include <QWidget>

namespace Ui {
class UserDataForm;
}

enum class UserRole : char;

class UserDataForm : public QWidget {
    Q_OBJECT

public:
    explicit UserDataForm(QWidget *parent = nullptr);
    ~UserDataForm();

    QString getLogin() const;
    void setLogin(const QString &login);

    QString getPassword() const;
    void setPassword(const QString &password);

    QString getRepeatPassword() const;
    void setRepeatPassword(const QString &repeatPassword);

    UserRole getRole() const;
    void setRole(UserRole role);

private:
    Ui::UserDataForm *ui;
};
