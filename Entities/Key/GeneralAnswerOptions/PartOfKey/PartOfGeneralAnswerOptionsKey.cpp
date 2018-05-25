#include "PartOfGeneralAnswerOptionsKey.h"

typedef PartOfGeneralAnswerOptionsKey POGAOK;

//  :: Lifecycle ::
POGAOK::PartOfGeneralAnswerOptionsKey() : PartOfKey() {
	getInternalAnswerOptionIndexes() = {0};
}

//  :: Accessors ::
//  :: Answer option index ::
uint POGAOK::getAnswerOptionIndex() const {
	return getInternalAnswerOptionIndexes().first();
}
void POGAOK::setAnswerOptionIndex(uint answerOptionIndex) {
	getInternalAnswerOptionIndexes().first() = answerOptionIndex;
}

//  :: Question indexes ::
Indexes POGAOK::getQuestionIndexes() const {
	return getInternalQuestionIndexes();
}
void POGAOK::setQuestionIndexes(const Indexes &questionIndexes) {
	getInternalQuestionIndexes() = questionIndexes;
}

//  :: Public methods ::

void POGAOK::addQuestionIndex(uint questionIndex) {
	auto &questionIndexes = getInternalQuestionIndexes();
	if (questionIndexes.indexOf(questionIndex) < 0) {
		questionIndexes.append(questionIndex);
	}
}

void POGAOK::deleteQuestionIndex(uint questionIndex) {
	getInternalQuestionIndexes().removeAll(questionIndex);
}
