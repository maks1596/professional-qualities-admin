#include "CreateUserModel.h"

#include <QJsonArray>
#include <QJsonValue>
#include <QStringList>

#include "Entities/User/User.h"
#include "Requester/Requester.h"

//  :: Constants ::

const QString PUT_USER_API = "users";
const QString GET_PROFESSIONS_API = "users/professions";

//  :: Lifecycle

CreateUserModel::CreateUserModel(QObject *parent/*= nullptr*/)
	: BaseService(parent) {}

//  :: Public methods ::

void CreateUserModel::putUser(const User &user) const {
	auto requester = makeRequester();
	connect(requester, SIGNAL(success()),
			SIGNAL(userPut()));
	requester->sendRequest(PUT_USER_API,
						   RequestType::PUT,
						   user.toJson());
}

void CreateUserModel::getProfessions() const {
	auto requester = makeRequester();
	connect(requester, SIGNAL(success(QJsonArray)),
			this, SLOT(jsonProfessionsGot(QJsonArray)));
	requester->sendRequest(GET_PROFESSIONS_API);
}

//  :: Private slots ::

void CreateUserModel::jsonProfessionsGot(const QJsonArray &jsonProfessions) const {
	QStringList professions;
	for (const auto &jsonValue : jsonProfessions) {
		if (jsonValue.isString()) {
			professions.append(jsonValue.toString());
		}
	}
	emit professionsGot(professions);
}
