#include "AddUserService.h"

#include "Entities/User/User.h"
#include "Requester/Requester.h"

//  :: Constants ::

const QString ADD_USER_API = "users";

//  :: Lifecycle ::

AddUserService::AddUserService(QObject *parent)
    : BaseService(parent)
{ }

//  :: Public methods ::

void AddUserService::addUser(const User &user) const {
    auto requester = makeRequester();
    connect(requester, SIGNAL(success()),
            SIGNAL(userAdded()));
    requester->sendRequest(ADD_USER_API,
                           RequestType::POST,
                           user.toJson());
}
