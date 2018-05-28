#include "PartOfKey.h"

#include <QList>
#include <QJsonArray>

#include "Entities/Key/GeneralAnswerOptions/PartOfKey/PartOfGeneralAnswerOptionsKey.h"
#include "Entities/Key/UniqueAnswerOptions/PartOfKey/PartOfUniqueAnswerOptionsKey.h"
#include "JsonArraySerialization.h"

//  :: Constants ::

const QString QUESTION_INDEXES_KEY = "questionIndexes";
const QString ANSWER_OPTION_INDEXES_KEY = "answerOptionIndexes";
const QString POINTS_KEY = "points";

//  :: Implementation ::

struct PartOfKey::Implementation {
	Indexes questionIndexes;
	Indexes answerOptionIndexes;
	uint points = 1;
};

//  :: Private function headers ::

QJsonArray toJsonArray(const Indexes &list);
Indexes fromJsonArray(const QJsonArray &jsonArray);

//  :: Lifecycle ::
//  :: Constructors ::
PartOfKey::PartOfKey() : pimpl(new Implementation()) {}

//  :: Copy ::
PartOfKey::PartOfKey(const PartOfKey &other)
	: pimpl(new Implementation(*other.pimpl))
{ }
PartOfKey &PartOfKey::operator=(const PartOfKey &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
PartOfKey::PartOfKey(PartOfKey &&other) : pimpl(other.pimpl.take()) {}
PartOfKey &PartOfKey::operator=(PartOfKey &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
PartOfKey::~PartOfKey() {}

//  :: Accessors ::
//  :: Points ::
uint PartOfKey::getPoints() const {
	return pimpl->points;
}
void PartOfKey::setPoints(const uint &points) {
	pimpl->points = points;
}

//  :: Transformations ::
//  :: To part of general answer options key ::
PartOfGeneralAnswerOptionsKey *PartOfKey::toPartOfGeneralAnswerOptionsKey() {
	return static_cast<PartOfGeneralAnswerOptionsKey *>(this);
}
const PartOfGeneralAnswerOptionsKey *PartOfKey::toPartOfGeneralAnswerOptionsKey() const {
	return static_cast<const PartOfGeneralAnswerOptionsKey *>(this);
}

PartOfGeneralAnswerOptionsKey *PartOfKey::toPOGAOK() {
	return toPartOfGeneralAnswerOptionsKey();
}
const PartOfGeneralAnswerOptionsKey *PartOfKey::toPOGAOK() const {
	return toPartOfGeneralAnswerOptionsKey();
}

//  :: To part of unique answer options key ::
PartOfUniqueAnswerOptionsKey *PartOfKey::toPartOfUniqueAnswerOptionsKey() {
	return static_cast<PartOfUniqueAnswerOptionsKey *>(this);
}
const PartOfUniqueAnswerOptionsKey *PartOfKey::toPartOfUniqueAnswerOptionsKey() const {
	return static_cast<const PartOfUniqueAnswerOptionsKey *>(this);
}

PartOfUniqueAnswerOptionsKey *PartOfKey::toPOUAOK() {
	return toPartOfUniqueAnswerOptionsKey();
}
const PartOfUniqueAnswerOptionsKey *PartOfKey::toPOUAOK() const {
	return toPartOfUniqueAnswerOptionsKey();
}

//  :: Serializable ::

QJsonObject PartOfKey::toJson() const {
	QJsonObject json;
	json[QUESTION_INDEXES_KEY] = toJsonArray(pimpl->questionIndexes);
	json[ANSWER_OPTION_INDEXES_KEY] = toJsonArray(pimpl->answerOptionIndexes);
	json[POINTS_KEY] = QJsonValue(static_cast<int>(pimpl->points));
	return json;
}

void PartOfKey::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(QUESTION_INDEXES_KEY) &&
			json[QUESTION_INDEXES_KEY].isArray()) {
		auto jsonQuestionIndexes = json[QUESTION_INDEXES_KEY].toArray();
		pimpl->questionIndexes = fromJsonArray(jsonQuestionIndexes);
	}
	if (json.contains(ANSWER_OPTION_INDEXES_KEY) &&
			json[ANSWER_OPTION_INDEXES_KEY].isArray()) {
		auto jsonAnswerOptionIndexes = json[ANSWER_OPTION_INDEXES_KEY].toArray();
		pimpl->answerOptionIndexes = fromJsonArray(jsonAnswerOptionIndexes);
	}
	if (json.contains(POINTS_KEY) &&
			json[POINTS_KEY].isDouble()) {
		pimpl->points = json[POINTS_KEY].toInt();
	}
}

//  :: Protected accessors ::
//  :: Question indexes ::
Indexes &PartOfKey::getInternalQuestionIndexes() {
	return pimpl->questionIndexes;
}
const Indexes &PartOfKey::getInternalQuestionIndexes() const {
	return pimpl->questionIndexes;
}

//  :: Answer option indexes ::
Indexes &PartOfKey::getInternalAnswerOptionIndexes() {
	return pimpl->answerOptionIndexes;
}
const Indexes &PartOfKey::getInternalAnswerOptionIndexes() const {
	return pimpl->answerOptionIndexes;
}

//  :: Private functions ::

QJsonArray toJsonArray(const Indexes &list) {
    return jsonArrayFromValues(list);
}

Indexes fromJsonArray(const QJsonArray &jsonArray) {
	QList<uint> list;
	for (const auto &json : jsonArray) {
		if (json.isDouble()) {
			list.append(json.toInt());
		}
	}
    return list;
}
