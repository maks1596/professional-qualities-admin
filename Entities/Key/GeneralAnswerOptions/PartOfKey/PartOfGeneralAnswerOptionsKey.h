#pragma once

#include "Entities/Key/PartOfKey/PartOfKey.h"

class PartOfGeneralAnswerOptionsKey : public PartOfKey {
public:
	//  :: Lifecycle ::
	PartOfGeneralAnswerOptionsKey();

	//  :: Accessors ::
	uint getAnswerOptionIndex() const;
	void setAnswerOptionIndex(uint answerOptionIndex);

	Indexes getQuestionIndexes() const;
	void setQuestionIndexes(const Indexes &questionIndexes);

	/**
	 * @brief Метод добавляет переданный индекс вопроса к уже сохранённым
	 * @param questionIndex - индекс вопроса
	 */
	void addQuestionIndex(uint questionIndex);

	/**
	 * @brief Метод удаляет переданный индекс вопроса из сохранённых
	 * @param questionIndex - индекс вопроса
	 */
	void deleteQuestionIndex(uint questionIndex);
};
