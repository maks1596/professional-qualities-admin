#pragma once

class QString;

enum class UserRole {
    User,
    Admin,
    AmountOfRoles
};

QString userRoleToJson(UserRole role);
QString userRoleToString(UserRole role);
