#include "UserRole.h"

#include <QString>

//  :: Constants ::

const QString JSON_USER_ROLE_USER = "User";
const QString JSON_USER_ROLE_ADMIN = "Admin";

const QString USER_ROLE_USER_STRING = "Пользователь";
const QString USER_ROLE_ADMIN_STRING = "Администратор";

//  :: Public functions ::

QString userRoleToJson(UserRole role) {
    switch (role) {
    case UserRole::User: return JSON_USER_ROLE_USER;
    case UserRole::Admin: return JSON_USER_ROLE_ADMIN;
    }
    return QString();
}

QString userRoleToString(UserRole role) {
    switch (role) {
    case UserRole::User: return USER_ROLE_USER_STRING;
    case UserRole::Admin: return USER_ROLE_ADMIN_STRING;
    }
    return QString();
}
