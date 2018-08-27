#pragma once

class QString;

enum class Gender {
    None,
	Male,
	Female
};

QString genderToString(Gender gender);
Gender genderFromString(const QString &string);

QString genderToJson(Gender gender);
Gender genderFromJson(const QString &string);
