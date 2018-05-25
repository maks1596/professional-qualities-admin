#include "ShortTestInfo.h"

#include <QString>

//  :: Constructors ::

const QString ID_JSON_KEY = "id";
const QString NAME_JSON_KEY = "name";

//  :: Implementation ::

struct ShortTestInfo::Implementation {
	QString name = "";
};

//  :: Lifecycle ::
//  :: Constructors ::
ShortTestInfo::ShortTestInfo(int id/*= 0*/,
							 const QString &name/*= ""*/)
	: Entity(id),
	  pimpl(new Implementation()) {
	setName(name);
}

//  :: Copy ::
ShortTestInfo::ShortTestInfo(const ShortTestInfo &other)
	: Entity(other),
	  pimpl(new Implementation(*other.pimpl))
{ }
ShortTestInfo &ShortTestInfo::operator=(const ShortTestInfo &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
ShortTestInfo::ShortTestInfo(ShortTestInfo &&other)
	: Entity(other),
	  pimpl(other.pimpl.take())
{ }
ShortTestInfo &ShortTestInfo::operator=(ShortTestInfo &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
ShortTestInfo::~ShortTestInfo() {}

//  :: Accessors ::

QString ShortTestInfo::getName() const {
	return pimpl->name;
}
void ShortTestInfo::setName(const QString &name) {
	pimpl->name = name;
}

//  :: Serializable ::

QJsonObject ShortTestInfo::toJson() const {
	QJsonObject json;

	json[ID_JSON_KEY] = getId();
	json[NAME_JSON_KEY] = getName();

	return json;
}

void ShortTestInfo::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(ID_JSON_KEY) && json[ID_JSON_KEY].isDouble()) {
		setId(json[ID_JSON_KEY].toInt());
	}
	if (json.contains(NAME_JSON_KEY) && json[NAME_JSON_KEY].isString()) {
		setName(json[NAME_JSON_KEY].toString());
	}
}
