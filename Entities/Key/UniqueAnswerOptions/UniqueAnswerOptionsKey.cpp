#include "UniqueAnswerOptionsKey.h"

#include "Entities/Key/PartOfKey/PartOfKey.h"
#include "Entities/Key/UniqueAnswerOptions/PartOfKey/PartOfUniqueAnswerOptionsKey.h"

const PartOfUniqueAnswerOptionsKey &UniqueAnswerOptionsKey::at(uint index) const {
	return *(static_cast<const Key *>(this)->at(index).toPOUAOK());
}
const PartOfUniqueAnswerOptionsKey &UniqueAnswerOptionsKey::operator[](uint index) const {
	return *(*static_cast<const Key *>(this))[index].toPOUAOK();
}
PartOfUniqueAnswerOptionsKey &UniqueAnswerOptionsKey::operator[](uint index) {
	return *(*static_cast<Key *>(this))[index].toPOUAOK();
}

uint UniqueAnswerOptionsKey::getCurrentQuestionIndex() const {
	return getCurrentPartOfKey().toPOUAOK()->getQuestionIndex();
}

void UniqueAnswerOptionsKey::replaceCurrentQuestionIndex(uint questionIndex) {
	getCurrentPartOfKey().toPOUAOK()->setQuestionIndex(questionIndex);
}

void UniqueAnswerOptionsKey::addQuestion(uint questionIndex) {
	PartOfUniqueAnswerOptionsKey partOfKey;
	partOfKey.setQuestionIndex(questionIndex);
	addPartOfKey(partOfKey);
}

void UniqueAnswerOptionsKey::addAnswerOptionToLastQuestion(uint answerOptionIndex) {
	getCurrentPartOfKey().toPOUAOK()->addAnswerOptionIndex(answerOptionIndex);
}

Indexes UniqueAnswerOptionsKey::getCurrentAnswerOptionIndexes() const {
	return getCurrentPartOfKey().toPOUAOK()->getAnswerOptionIndexes();
}

void UniqueAnswerOptionsKey::deleteAnswerOptionFromCurrentQuestion(uint answerOptionIndex) {
	getCurrentPartOfKey().toPOUAOK()->deleteAnswerOptionIndex(answerOptionIndex);
}

void UniqueAnswerOptionsKey::setAnswerOptionsForCurrentQuestion(const Indexes &answerOptionIndexes) {
	getCurrentPartOfKey().toPOUAOK()->setAnswerOptionIndexes(answerOptionIndexes);
}

void UniqueAnswerOptionsKey::deleteQuestion(uint questionIndex, uint points/*= 1*/) {
	QMutableListIterator<PartOfKey> iter(getPartsOfKey());
	while (iter.hasNext()) {
		iter.next();
		if (iter.value().toPOUAOK()->getQuestionIndex() == questionIndex &&
				iter.value().getPoints() == points) {
			iter.remove();
		}
	}
	getCurrentPartOfKey() = PartOfKey();
}
