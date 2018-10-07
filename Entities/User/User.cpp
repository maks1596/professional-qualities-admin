#include "User.h"

#include <QDate>
#include <QString>

#include "Entities/Gender/Gender.h"
#include "Entities/UserRole/UserRole.h"

//  :: Constants ::

const QString ID_JSON_KEY = "id";
const QString LOGIN_JSON_KEY = "login";
const QString PASSWORD_JSON_KEY = "password";
const QString ROLE_JSON_KEY = "roleName";
const QString NAME_JSON_KEY = "name";
const QString GENDER_JSON_KEY = "gender";
const QString BIRTHDAY_JSON_KEY = "birthday";
const QString PROFESSION_JSON_KEY = "professionName";
const QString EXPERT_ASSESSMENT_JSON_KEY = "expertAssessment";

//  :: Implementation ::

struct User::Implementation {
	QString login;
	QString password;
    UserRole role;

	QString name;
	Gender gender = Gender::Male;
    QDate birthdate = QDate::currentDate();
	QString profession;
	int expertAssessment = -1;
};

//  :: Lifecycle ::
//  :: Constructors ::
User::User(int id/*= 0*/)
	: Entity(id),
	  pimpl(new Implementation)
{ }

//  :: Copy ::
User::User(const User &other)
	: QObject(other.parent()),
	  Entity(other),
	  pimpl(new Implementation(*other.pimpl))
{ }
User &User::operator=(const User &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
User::User(User &&other) noexcept
	: Entity(other),
	  pimpl(other.pimpl.take()) {}
User &User::operator=(User &&other) noexcept {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
User::~User() {}

//  :: Accessors ::
//  :: Login ::
QString User::getLogin() const {
	return pimpl->login;
}
void User::setLogin(const QString &login) {
	pimpl->login = login;
}

//  :: Password ::
QString User::getPassword() const {
	return pimpl->password;
}
void User::setPassword(const QString &password) {
    pimpl->password = password;
}

//  :: Role ::
UserRole User::getRole() const {
    return pimpl->role;
}
void User::setRole(UserRole role) {
    pimpl->role = role;
}

//  :: Name ::
QString User::getName() const {
	return pimpl->name;
}
void User::setName(const QString &name) {
	pimpl->name = name;
}

//  :: Gender ::
Gender User::getGender() const {
	return pimpl->gender;
}
void User::setGender(Gender gender) {
	pimpl->gender = gender;
}

QString User::getGenderString() const {
	return genderToString(getGender());
}
void User::setGenderString(const QString &genderString) {
	setGender(genderFromString(genderString));
}

//  :: Birthday ::
QDate User::getBirthdate() const {
    return pimpl->birthdate;
}
void User::setBirthdate(const QDate &birthdate) {
    pimpl->birthdate = birthdate;
}
//  :: Age ::
uint User::getAge() const {
	QDate currentDate = QDate::currentDate();
	int age = currentDate.year() - getBirthdate().year();

	if (getBirthdate().month() > currentDate.month() ||
		(getBirthdate().month() == currentDate.month() &&
			getBirthdate().day() > currentDate.day())) {
		age--;
	}
	return age;
}

//  :: Profession ::
QString User::getProfession() const {
	return pimpl->profession;
}
void User::setProfession(const QString &profession) {
	pimpl->profession = profession;
}

//  :: Expert assessment ::
int User::getExpertAssessment() const {
	return pimpl->expertAssessment;
}
void User::setExpertAssessment(int expertAssessment) {
	pimpl->expertAssessment = expertAssessment;
}

//  :: Serializable ::

QJsonObject User::toJson() const {
	QJsonObject json;

	json[ID_JSON_KEY] = getId();
	json[LOGIN_JSON_KEY] = getLogin();
	json[PASSWORD_JSON_KEY] = getPassword();
    json[ROLE_JSON_KEY] = userRoleToJson(getRole());
	json[NAME_JSON_KEY] = getName();
	json[GENDER_JSON_KEY] = genderToJson(getGender());
	json[BIRTHDAY_JSON_KEY] = getBirthdate().toString(Qt::DateFormat::ISODate);
	json[PROFESSION_JSON_KEY] = getProfession();
	json[EXPERT_ASSESSMENT_JSON_KEY] = getExpertAssessment();

	return json;
}

void User::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(ID_JSON_KEY) && json[ID_JSON_KEY].isDouble()) {
		setId(json[ID_JSON_KEY].toInt());
	}
	if (json.contains(LOGIN_JSON_KEY) && json[LOGIN_JSON_KEY].isString()) {
		setLogin(json[LOGIN_JSON_KEY].toString());
    }
	if (json.contains(PASSWORD_JSON_KEY) && json[PASSWORD_JSON_KEY].isString()) {
		setPassword(json[PASSWORD_JSON_KEY].toString());
    }
    if (json.contains(ROLE_JSON_KEY) && json[ROLE_JSON_KEY].isString()) {
        auto roleJsonString = json[ROLE_JSON_KEY].toString();
        auto role = userRoleFromJson(roleJsonString);
        setRole(role);
    }
	if (json.contains(NAME_JSON_KEY) && json[NAME_JSON_KEY].isString()) {
		setName(json[NAME_JSON_KEY].toString());
    }
	if (json.contains(GENDER_JSON_KEY) && json[GENDER_JSON_KEY].isString()) {
		auto genderJsonString = json[GENDER_JSON_KEY].toString();
		auto gender = genderFromJson(genderJsonString);
		setGender(gender);
    }
	if (json.contains(BIRTHDAY_JSON_KEY) && json[BIRTHDAY_JSON_KEY].isString()) {
		auto birthdayString = json[BIRTHDAY_JSON_KEY].toString();
		auto birthday = QDate::fromString(birthdayString,
										  Qt::DateFormat::ISODate);
		setBirthdate(birthday);
    }
	if (json.contains(PROFESSION_JSON_KEY) && json[PROFESSION_JSON_KEY].isString()) {
		setProfession(json[PROFESSION_JSON_KEY].toString());
    }
	if (json.contains(EXPERT_ASSESSMENT_JSON_KEY) &&
			json[EXPERT_ASSESSMENT_JSON_KEY].isDouble()) {
		setExpertAssessment(json[EXPERT_ASSESSMENT_JSON_KEY].toInt());
    }
}
