#pragma once

class QString;

enum class UserRole {
    User,
    Admin,
    AmountOfRoles
};

QString userRoleToJson(UserRole role);
UserRole userRoleFromJson(const QString &json);

QString userRoleToString(UserRole role);
