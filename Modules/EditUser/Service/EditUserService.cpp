#include "EditUserService.h"

#include "Entities/User/User.h"
#include "Requester/Requester.h"

//  :: Constatns ::

const QString PATCH_USER_API = "users";

//  :: Lifecycle ::

EditUserService::EditUserService(QObject *parent)
    : BaseService(parent) { }

//  :: Public methods ::

void EditUserService::patchUser(const User &user) {
    auto requester = makeRequesterWithDefaultErrorOutput();
    connect(requester, SIGNAL(success()), SIGNAL(userPatched()));
    requester->sendRequest(PATCH_USER_API,
                           RequestType::PATCH,
                           user.toJson());
}
