#include "PartOfUniqueAnswerOptionsKey.h"

typedef PartOfUniqueAnswerOptionsKey POUAOK;

//  :: Lifecycle ::
POUAOK::PartOfUniqueAnswerOptionsKey() : PartOfKey() {
	getInternalQuestionIndexes() = {0};
}

//  :: Accessors ::
//  :: Question index ::
uint POUAOK::getQuestionIndex() const {
	return getInternalQuestionIndexes().first();
}
void POUAOK::setQuestionIndex(uint questionIndex) {
	getInternalQuestionIndexes().first() = questionIndex;
}

//  :: Answer option indexes ::
Indexes POUAOK::getAnswerOptionIndexes() const {
	return getInternalAnswerOptionIndexes();
}
void POUAOK::setAnswerOptionIndexes(const Indexes &answerOptionIndexes) {
	getInternalAnswerOptionIndexes() = answerOptionIndexes;
}

void POUAOK::addAnswerOptionIndex(uint answerOptionIndex) {
	auto &answerOptionIndexes = getInternalAnswerOptionIndexes();
	if (answerOptionIndexes.indexOf(answerOptionIndex) < 0) {
		answerOptionIndexes.append(answerOptionIndex);
	}
}

void POUAOK::deleteAnswerOptionIndex(uint answerOptionIndex) {
	getInternalAnswerOptionIndexes().removeAll(answerOptionIndex);
}
