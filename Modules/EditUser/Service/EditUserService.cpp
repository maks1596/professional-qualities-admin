#include "EditUserService.h"

#include "Entities/User/User.h"
#include "Requester/Requester.h"

//  :: Constatns ::

const QString UPDATE_USER_API = "users";

//  :: Lifecycle ::

EditUserService::EditUserService(QObject *parent)
    : BaseService(parent) { }

//  :: Public methods ::

void EditUserService::updateUser(const User &user) {
    auto requester = makeRequesterWithDefaultErrorOutput();
    connect(requester, SIGNAL(success()), SIGNAL(userUpdated()));
    requester->sendRequest(UPDATE_USER_API,
                           RequestType::PUT,
                           user.toJson());
}
