#include "UsersModel.h"

#include <QJsonArray>
#include <QJsonValue>

#include "Requester/Requester.h"
#include "Entities/User/User.h"
#include "JsonArraySerialization.h"

//  :: Constants ::

const QString GET_USERS_API = "users";
const QString GET_USER_API = "users/%1";
const QString DELETE_USER_API = GET_USER_API;

//  :: Lifecycle ::

UsersModel::UsersModel(QObject *parent/*= nullptr*/)
	: BaseService(parent) {}

//  :: Public methods ::

void UsersModel::getUsers() const {
	auto *requester = makeRequester();
	connect(requester, SIGNAL(success(QJsonArray)),
			this, SLOT(jsonUsersGot(QJsonArray)));
	requester->sendRequest(GET_USERS_API);
}


void UsersModel::getUser(int userId) const {
	auto *requester = makeRequester();
	connect(requester, SIGNAL(success(QJsonObject)),
			this, SLOT(jsonUserGot(QJsonObject)));
	requester->sendRequest(GET_USER_API.arg(userId));
}

void UsersModel::deleteUser(int userId) const {
	auto *requester = makeRequester();
	connect(requester, SIGNAL(success(QJsonArray)),
			this, SIGNAL(userDeleted()));
	requester->sendRequest(DELETE_USER_API.arg(userId),
						   RequestType::DELET);
}

//  :: Private slots ::

void UsersModel::jsonUsersGot(const QJsonArray &jsonUsers) {
    auto users = serializableObjectsFromJsonArray<QList, User>(jsonUsers);
	emit usersGot(users);
}

void UsersModel::jsonUserGot(const QJsonObject &jsonUser) {
    auto user = makeWithJsonObject<User>(jsonUser);
    emit userGot(user);
}
