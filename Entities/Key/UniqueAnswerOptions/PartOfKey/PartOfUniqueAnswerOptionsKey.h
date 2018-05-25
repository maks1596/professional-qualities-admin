#pragma once

#include "Entities/Key/PartOfKey/PartOfKey.h"

class PartOfUniqueAnswerOptionsKey : public PartOfKey {
public:
	//  :: Lifecycle ::
	PartOfUniqueAnswerOptionsKey();
	virtual ~PartOfUniqueAnswerOptionsKey() noexcept = default;

	//  :: Accessors ::
	uint getQuestionIndex() const;
	void setQuestionIndex(uint questionIndex);

	Indexes getAnswerOptionIndexes() const;
	void setAnswerOptionIndexes(const Indexes &answerOptionIndexes);

	/**
	 * @brief Метод добавляет переданный индекс варианта ответа к уже сохранённым
	 * @param answerOptionIndex - индекс варианта ответа
	 */
	void addAnswerOptionIndex(uint answerOptionIndex);

	/**
	 * @brief Метод удаляет переданный индекс варианта ответа из сохранённых
	 * @param answerOptionIndex - индекс варианта ответа
	 */
	void deleteAnswerOptionIndex(uint answerOptionIndex);
};
