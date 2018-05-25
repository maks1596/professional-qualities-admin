#pragma once

#include "Entities/Key/Key.h"

class PartOfGeneralAnswerOptionsKey;

class GeneralAnswerOptionsKey : public Key {
public:

	// Методы возвращают ссылку на часть ключа,
	// соответствующую переданному индексу
	const PartOfGeneralAnswerOptionsKey &at(uint index) const;
	const PartOfGeneralAnswerOptionsKey &operator[](uint index) const;
	PartOfGeneralAnswerOptionsKey &operator[](uint index);

	/**
	 * @brief Метод возвращает индекс последнего варианта ответа
	 * @return индекс последнего варианта ответа
	 */
	uint getCurrentAnswerOptionIndex() const;

	/**
	 * @brief Метод запоминает индекс нового варинта ответа
	 * @param answerOptionIndex - индекс нового варианта ответа
	 */
	void addAnswerOption(uint answerOptionIndex);

	/**
	 * @brief Метод добавляет индекс вопроса к последнему добавленному варианту ответа
	 * @param questionIndex - индекс варианта ответа
	 */
	void addQuestionToLastAnswerOption(uint questionIndex);

	/**
	 * @brief Метод возвращает индексы вопросов от последнего добавленного
	 * варианта ответа
	 * @return индексы вопросов
	 */
	Indexes getCurrentQuestionIndexes() const;

	/**
	 * @brief Метод удаляет вопрос с переданным индексом из текущего варианта ответа
	 * @param questionIndex - индекс вопроса
	 */
	void deleteQuestionFromCurrentAnswerOption(uint questionIndex);

	/**
	 * @brief Метод удаляет вариант ответа с переданным количеством баллов
	 * @param answerOptionIndex - индекс варианта ответа
	 * @param points - количество баллов
	 */
	void deleteAnswerOption(uint answerOptionIndex, uint points);
};
