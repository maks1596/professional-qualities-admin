#include "AutorizationData.h"

#include <QString>

//  :: Constants ::

const QString LOGIN_JSON_KEY = "login";
const QString PASSWORD_JSON_KEY = "password";

//  :: Implementation ::

struct AutorizationData::Implementation {
	QString login;
	QString password;
};

//  :: Lifecycle ::
//  :: Constructors ::
AutorizationData::AutorizationData()
	: pimpl(new Implementation())
{ }

AutorizationData::AutorizationData(const QString login,
								   const QString password)
	: AutorizationData()
{
	setLogin(login);
	setPassword(password);
}

//  :: Copy ::
AutorizationData::AutorizationData(const AutorizationData &other)
	: pimpl(new Implementation(*other.pimpl))
{ }
AutorizationData &AutorizationData::operator=(const AutorizationData &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
AutorizationData::AutorizationData(AutorizationData &&other) : pimpl(other.pimpl.take())
{ }
AutorizationData &AutorizationData::operator=(AutorizationData &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
AutorizationData::~AutorizationData() { }

//  :: Accessors ::
//  :: Login ::
QString AutorizationData::getLogin() const {
	return pimpl->login;
}
void AutorizationData::setLogin(const QString &login) {
	pimpl->login = login;
}

//  :: Password ::
QString AutorizationData::getPassword() const {
	return pimpl->password;
}
void AutorizationData::setPassword(const QString &password) {
	pimpl->password = password;
}

//  :: Serializable ::

QJsonObject AutorizationData::toJson() const {
	QJsonObject json;

	json[LOGIN_JSON_KEY] = getLogin();
	json[PASSWORD_JSON_KEY] = getPassword();

	return json;
}
void AutorizationData::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(LOGIN_JSON_KEY) && json[LOGIN_JSON_KEY].isString()) {
		setLogin(json[LOGIN_JSON_KEY].toString());
	}
	if (json.contains(PASSWORD_JSON_KEY) && json[PASSWORD_JSON_KEY].isString()) {
		setPassword(json[PASSWORD_JSON_KEY].toString());
	}
}
