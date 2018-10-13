#include "UsersService.h"

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

UsersService::UsersService(QObject *parent/*= nullptr*/)
	: BaseService(parent) {}

//  :: Public methods ::

void UsersService::getUsers() const {
	auto *requester = makeRequesterWithDefaultErrorOutput();
	connect(requester, SIGNAL(success(QJsonArray)),
			this, SLOT(jsonUsersGot(QJsonArray)));
	requester->sendRequest(GET_USERS_API);
}

void UsersService::removeUser(int userId) const {
	auto *requester = makeRequesterWithDefaultErrorOutput();
	connect(requester, SIGNAL(success(QJsonArray)),
            this, SIGNAL(userRemoved()));
	requester->sendRequest(DELETE_USER_API.arg(userId),
						   RequestType::DELET);
}

//  :: Private slots ::

void UsersService::jsonUsersGot(const QJsonArray &jsonUsers) {
    auto users = serializableObjectsFromJsonArray<QList, User>(jsonUsers);
	emit usersGot(users);
}
