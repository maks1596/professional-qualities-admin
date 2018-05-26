#include "UpdateUserDataModel.h"

#include "Entities/User/User.h"
#include "Requester/Requester.h"

//  :: Constants ::

const QString PATCH_USER_API = "users";

//  :: Lifecycle ::

UpdateUserDataModel::UpdateUserDataModel(QObject *parent/*= nullptr*/)
	: BaseService(parent) {}

//  :: Public methods ::

void UpdateUserDataModel::patchUser(const User &user) const {
	auto requester = makeRequester();
	connect(requester, SIGNAL(success()),
			SIGNAL(userPatched()));
	requester->sendRequest(PATCH_USER_API,
						   RequestType::PATCH,
						   user.toJson());
}
