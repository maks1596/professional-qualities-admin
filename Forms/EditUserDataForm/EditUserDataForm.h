#pragma once

#include <QWidget>

namespace Ui {
class EditUserDataForm;
}

enum class UserRole;

class EditUserDataForm : public QWidget {
    Q_OBJECT

public:
    explicit EditUserDataForm(QWidget *parent = nullptr);
    ~EditUserDataForm();

    QString getLogin() const;
    void setLogin(const QString &login);

    QString getPassword() const;
    void setPassword(const QString &password);

    UserRole getRole() const;
    void setRole(const UserRole &role);

signals:
    void passwordChanged(const QString &password);
    void roleChanged(UserRole role);

private slots:
    void onRoleComboBoxCurrentIndexChanged(int index);

private:
    Ui::EditUserDataForm *ui;
};
