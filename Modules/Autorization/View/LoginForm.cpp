#include "LoginForm.h"
#include "ui_LoginForm.h"

#include "../Model/AutorizationModel.h"

//  :: Lifecycle ::

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

	configureErrorMessage();
	initModel();

    connect(ui->login, &QLineEdit::returnPressed,
            [&] { ui->password->setFocus(); });
    connect(ui->password, &QLineEdit::returnPressed,
            ui->loginBtn, &QPushButton::click);

    connect(ui->login, &QLineEdit::textEdited,
            ui->errorMessage, &QLabel::hide);
    connect(ui->password, &QLineEdit::textEdited,
            ui->errorMessage, &QLabel::hide);

    connect(ui->loginBtn, &QPushButton::clicked,
            this, &LoginForm::onLoginBtnClicked);

#ifdef QT_DEBUG
	ui->login->setText("admin");
    ui->password->setText("password");
#endif
}

LoginForm::~LoginForm() {
    delete ui;
}

//  :: Private slots ::

void LoginForm::onLoginBtnClicked() {
	m_model->autorizeAsAdmin(ui->login->text(),
							 ui->password->text());
}

void LoginForm::onLoginSuccess() {
	emit loginSuccessed();
	hide();
}

void LoginForm::onLoginFailed() {
	ui->errorMessage->show();
	QApplication::alert(this);
}

//  :: Private methods ::

void LoginForm::configureErrorMessage() {
	ui->errorMessage->setStyleSheet("QLabel {color : red; }");
	ui->errorMessage->hide();
}

void LoginForm::initModel() {
	m_model = new AutorizationModel(this);
	connect(m_model, &AutorizationModel::autorized,
			this, &LoginForm::onLoginSuccess);
	connect(m_model, &AutorizationModel::error,
			this, &LoginForm::onLoginFailed);
}
