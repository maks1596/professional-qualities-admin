#pragma once

#include <QWidget>

class AutorizationModel;

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget {
Q_OBJECT

public:
	explicit LoginForm(QWidget *parent = nullptr);
	virtual ~LoginForm() noexcept;

signals:
    void loginSuccessed();

private slots:
    void onLoginBtnClicked();

	void onLoginSuccess();
	void onLoginFailed();

private:
	void configureErrorMessage();
	void initModel();

    Ui::LoginForm *ui;
	AutorizationModel *m_model;
};
