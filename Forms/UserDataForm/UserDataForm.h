#pragma once

#include <QWidget>

namespace Ui {
class UserDataForm;
}

enum class UserRole;
enum class PasswordsHintStatus;

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

    void setPasswordsHintStatus(PasswordsHintStatus status);

signals:
    void loginChanged(const QString &login);
    void passwordChanged(const QString &login);
    void repeatPasswordChanged(const QString &login);
    void roleChanged(UserRole role);

private slots:
    void onRoleComboBoxCurrentIndexChanged(int index);

private:
    void setPasswordHintLabelTextColor(const QString &color);

    Ui::UserDataForm *ui;
};
