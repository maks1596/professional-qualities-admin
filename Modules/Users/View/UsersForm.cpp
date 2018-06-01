#include "UsersForm.h"

#include <QMessageBox>

#include "Entities/User/User.h"
#include "../Model/UsersModel.h"

//  :: Constants ::

const QStringList kHeaderLabels {
    "Имя",
    "Пол",
    "Возраст",
    "Профессия",
    "Оценка эксперта"
};

const QString TITLE = "Тестируемые";
const QString ADD_BUTTON_ICON_NAME = ":/images/account-plus.svg";
const QString ADD_BUTTON_TOOL_TIP = "Добавить тестируемого";

//  :: Lifecycle ::

UsersForm::UsersForm(QWidget *parent) :
	EntitiesForm(parent)
{
    setTitle(TITLE);
    setAddButtonIconName(ADD_BUTTON_ICON_NAME);
    setAddButtonToolTip(ADD_BUTTON_TOOL_TIP);
    setHeaderLabels(kHeaderLabels);

	m_model = new UsersModel(this);
	connect(m_model, &UsersModel::usersGot,
			this, &UsersForm::updateUsersTable);
	connect(m_model, &UsersModel::userGot,
			this, &UsersForm::createUserForm);
	connect(m_model, &UsersModel::error,
			this, &UsersForm::error);
}

//  :: Abstract methods ::

void UsersForm::update() {
	m_model->getUsers();
}

//  :: Protected slots ::

void UsersForm::onAddBtnClicked() {
    emit createUserForm(User());
}

void UsersForm::editEntity(const int &userID) {
	m_model->getUser(userID);
}

void UsersForm::removeEntity(const int &userID) {
    int btn = QMessageBox::question(this, "Удаление пользователя",
                                    "Вы действительно хотите удалить пользователя?",
                                    QMessageBox::Yes, QMessageBox::No);
    if(btn == QMessageBox::Yes) {
		m_model->deleteUser(userID);
    }
}

//  :: Private slots ::

void UsersForm::updateUsersTable(const QList<User> &users) {
	QList<Entity> entities;
	QList<QStringList> content;

	for (const auto &user : users) {
		QString name = user.getName().isEmpty() ?
						   user.getLogin() :
						   user.getName();
		QString expertAssessmentString = user.getExpertAssessment() != -1 ?
										 QString("%1").arg(user.getExpertAssessment()) :
										 QString();
		content.append({name,
						user.getGenderString(),
						QString("%1").arg(user.getAge()),
						user.getProfession(),
						expertAssessmentString});
		entities.append(user);
	}

	setContent(content);
	setEntities(entities);
}
