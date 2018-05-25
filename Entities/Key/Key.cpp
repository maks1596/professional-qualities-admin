#include "Key.h"

#include <QList>

#include "Entities/Key/GeneralAnswerOptions/GeneralAnswerOptionsKey.h"
#include "Entities/Key/UniqueAnswerOptions/UniqueAnswerOptionsKey.h"
#include "PartOfKey/PartOfKey.h"

struct Key::Implementation {
	QList<PartOfKey> partsOfKey;
	int currentPartOfKeyIndex;
};

//  :: Lifecycle ::
//  :: Constructors ::
Key::Key() : pimpl(new Implementation())
{ }

//  :: Copy ::
Key::Key(const Key &other)
	: pimpl(new Implementation(*other.pimpl))
{ }
Key &Key::operator=(const Key &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
Key::Key(Key &&other) : pimpl(other.pimpl.take())
{ }
Key &Key::operator=(Key &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
Key::~Key() { }

//  :: Accessors ::
//  :: Parts of key ::
const PartOfKey &Key::at(uint index) const {
	return pimpl->partsOfKey.at(index);
}
const PartOfKey &Key::operator[](uint index) const {
	return pimpl->partsOfKey[index];
}
PartOfKey &Key::operator[](uint index) {
	return pimpl->partsOfKey[index];
}

//  :: Public methods ::

uint Key::amountOfParts() const {
	return pimpl->partsOfKey.size();
}

void Key::addPartOfKey(const PartOfKey &partOfKey) {
	getPartsOfKey().append(partOfKey);
	setCurrentPartOfKeyIndex(getPartsOfKey().size() - 1);
}

void Key::deletePartOfKey(uint index) {
	pimpl->partsOfKey.removeAt(index);
}

//  ::  Points ::

void Key::setPoints(const uint &points) {
	getCurrentPartOfKey().setPoints(points);
}

uint Key::getPoints() const {
	return getCurrentPartOfKey().getPoints();
}

//  :: Transformations ::

GeneralAnswerOptionsKey *Key::toGeneralAnswerOptionsKey() {
	return static_cast<GeneralAnswerOptionsKey *>(this);
}
GeneralAnswerOptionsKey *Key::toGAOK() {
	return toGeneralAnswerOptionsKey();
}

UniqueAnswerOptionsKey *Key::toUniqueAnswerOptionsKey() {
	return static_cast<UniqueAnswerOptionsKey *>(this);
}
UniqueAnswerOptionsKey *Key::toUAOK() {
	return toUniqueAnswerOptionsKey();
}

//  :: Serializable ::

QJsonArray Key::toJson() const {
	QJsonArray json;
	for (const auto &partOfKey : pimpl->partsOfKey) {
		json.append(partOfKey.toJson());
	}
	return json;
}

void Key::initWithJsonArray(const QJsonArray &json) {
	pimpl->partsOfKey.clear();
	for (const auto &jsonPartOfKey : json) {
		if (jsonPartOfKey.isObject()) {
			QJsonObject jsonObject = jsonPartOfKey.toObject();
			PartOfKey partOfKey;
			partOfKey.initWithJsonObject(jsonObject);
			pimpl->partsOfKey.append(partOfKey);
		}
	}
}

//  :: Protected accessors ::
//  :: Parts of key ::
QList<PartOfKey> &Key::getPartsOfKey() {
	return pimpl->partsOfKey;
}
const QList<PartOfKey> &Key::getPartsOfKey() const {
	return pimpl->partsOfKey;
}

//  :: Current part of key ::
PartOfKey &Key::getCurrentPartOfKey() {
	return getPartsOfKey()[getCurrentPartOfKeyIndex()];
}
const PartOfKey &Key::getCurrentPartOfKey() const {
	return getPartsOfKey()[getCurrentPartOfKeyIndex()];
}

//  :: Private accessors ::
int Key::getCurrentPartOfKeyIndex() const {
	return pimpl->currentPartOfKeyIndex;
}
void Key::setCurrentPartOfKeyIndex(int index) {
	pimpl->currentPartOfKeyIndex = index;
}
