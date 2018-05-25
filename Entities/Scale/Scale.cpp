#include "Scale.h"

#include <QJsonArray>

#include "Entities/EvaluationMap/EvaluationMap.h"
#include "Entities/Key/Key.h"

//  :: Constants ::

const QString ID_JSON_KEY = "id";
const QString NAME_JSON_KEY = "name";
const QString KEY_KEY = "key";
const QString EVALUATION_MAP_KEY = "evaluationMap";

//  :: Implementation ::

struct Scale::Implementation {
	int id = 0;
	QString name;

	Key key;
	EvaluationMap evaluationMap;
};

//  :: Lifecycle ::
//  :: Constructors ::
Scale::Scale() : pimpl(new Implementation()) {}
Scale::Scale(const int &id) : Scale() {
	setId(id);
}
Scale::Scale(const QString &name) : Scale() {
	setName(name);
}
Scale::Scale(const int &id, const QString &name) : Scale() {
	setId(id);
	setName(name);
}

//  :: Copy ::
Scale::Scale(const Scale &other)
	: pimpl(new Implementation(*other.pimpl))
{ }
Scale &Scale::operator=(const Scale &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
Scale::Scale(Scale &&other) : pimpl(other.pimpl.take()) {}
Scale &Scale::operator=(Scale &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
Scale::~Scale() {}

//  :: Accessors ::
//  :: ID ::
int Scale::getId() const {
	return pimpl->id;
}
void Scale::setId(const int &id) {
	pimpl->id = id;
}

//  :: Name ::
QString Scale::getName() const {
	return pimpl->name;
}
void Scale::setName(const QString &name) {
	pimpl->name = name;
}

//  :: Key ::
Key *Scale::getKey() {
	return &pimpl->key;
}
GeneralAnswerOptionsKey *Scale::getGeneralAnswerOptionsKey() {
	return getKey()->toGAOK();
}
UniqueAnswerOptionsKey *Scale::getUniqueAnswerOptionsKey() {
	return getKey()->toUAOK();
}

//  :: Evaluation Map ::
EvaluationMap *Scale::getEvaluationMap() {
	return &pimpl->evaluationMap;
}

//  :: Serializable ::

QJsonObject Scale::toJson() const {
    QJsonObject result;

	result[ID_JSON_KEY] = pimpl->id;
	result[NAME_JSON_KEY] = pimpl->name;
	result[KEY_KEY] = pimpl->key.toJson();
	result[EVALUATION_MAP_KEY] = pimpl->evaluationMap.toJson();

    return result;
}

void Scale::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(ID_JSON_KEY) && json[ID_JSON_KEY].isDouble()) {
		pimpl->id = json[ID_JSON_KEY].toInt();
    }
	if (json.contains(NAME_JSON_KEY) && json[NAME_JSON_KEY].isString()) {
		pimpl->name = json[NAME_JSON_KEY].toString();
    }
	if (json.contains(KEY_KEY) && json[KEY_KEY].isArray()) {
		pimpl->key.initWithJsonArray(json[KEY_KEY].toArray());
    }
	if (json.contains(EVALUATION_MAP_KEY) && json[EVALUATION_MAP_KEY].isArray()) {
		pimpl->evaluationMap.initWithJsonArray(json[EVALUATION_MAP_KEY].toArray());
    }
}

//  :: Public functions ::

bool operator==(const Scale &lhs, const Scale &rhs) {
	return lhs.getName() == rhs.getName();
}
