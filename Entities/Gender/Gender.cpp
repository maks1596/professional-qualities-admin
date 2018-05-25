#include "Gender.h"

#include <QString>

//  :: Constants

const QString MALE_GENDER_STRING = "Мужской";
const QString FEMALE_GENDER_STRING = "Женский";

const QString MALE_GENDER_JSON_STRING = "Male";
const QString FEMALE_GENDER_JSON_STRING = "Female";

//  :: Public functions ::
//  :: to string ::
QString genderToString(Gender gender) {
	switch (gender) {
	case Gender::Male:
		return MALE_GENDER_STRING;
	case Gender::Female:
		return FEMALE_GENDER_STRING;
	}
	return QString();
}

Gender genderFromString(const QString &string) {
	if (string == FEMALE_GENDER_STRING) {
		return Gender::Female;
	} else {
		return Gender::Male;
	}
}

//  :: to json ::
QString genderToJson(Gender gender) {
	switch (gender) {
	case Gender::Male:
		return MALE_GENDER_JSON_STRING;
	case Gender::Female:
		return FEMALE_GENDER_JSON_STRING;
	}
	return MALE_GENDER_JSON_STRING;
}
Gender genderFromJson(const QString &string) {
	if (string == FEMALE_GENDER_JSON_STRING) {
		return Gender::Female;
	} else {
		return Gender::Male;
	}
}
