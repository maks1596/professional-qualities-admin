#include "GeneralAnswerOptionsKey.h"

#include "Entities/Key/GeneralAnswerOptions/PartOfKey/PartOfGeneralAnswerOptionsKey.h"
#include "Entities/Key/PartOfKey/PartOfKey.h"

//  :: Public methods ::
//  :: Индексация ::
const PartOfGeneralAnswerOptionsKey &GeneralAnswerOptionsKey::at(uint index) const {
	return *(static_cast<const Key *>(this)->at(index).toPOGAOK());
}
const PartOfGeneralAnswerOptionsKey &GeneralAnswerOptionsKey::operator[](uint index) const {
	return *(*static_cast<const Key *>(this))[index].toPOGAOK();
}
PartOfGeneralAnswerOptionsKey &GeneralAnswerOptionsKey::operator[](uint index) {
	return *(*static_cast<Key *>(this))[index].toPOGAOK();
}

//  :: --------------------------------------- ::

uint GeneralAnswerOptionsKey::getCurrentAnswerOptionIndex() const {
	return getCurrentPartOfKey().toPOGAOK()->getAnswerOptionIndex();
}

void GeneralAnswerOptionsKey::addAnswerOption(uint answerOptionIndex) {
	PartOfGeneralAnswerOptionsKey partOfKey;
	partOfKey.setAnswerOptionIndex(answerOptionIndex);
	addPartOfKey(partOfKey);
}

void GeneralAnswerOptionsKey::addQuestionToLastAnswerOption(uint questionIndex) {
	getCurrentPartOfKey().toPOGAOK()->addQuestionIndex(questionIndex);
}

Indexes GeneralAnswerOptionsKey::getCurrentQuestionIndexes() const {
	return getCurrentPartOfKey().toPOGAOK()->getQuestionIndexes();
}

void GeneralAnswerOptionsKey::deleteQuestionFromCurrentAnswerOption(uint questionIndex) {
	getCurrentPartOfKey().toPOGAOK()->deleteQuestionIndex(questionIndex);
}

void GeneralAnswerOptionsKey::deleteAnswerOption(uint answerOptionIndex, uint points) {
	QMutableListIterator<PartOfKey> iter(getPartsOfKey());
	while (iter.hasNext()) {
		iter.next();
		if (iter.value().toPOGAOK()->getAnswerOptionIndex() == answerOptionIndex &&
				iter.value().getPoints() == points) {
			iter.remove();
		}
	}
	getCurrentPartOfKey() = PartOfKey();
}
