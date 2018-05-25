#pragma once

#include "Entities/Key/Key.h"

class PartOfUniqueAnswerOptionsKey;

class UniqueAnswerOptionsKey : public Key {
public:

	// Методы возвращают ссылку на часть ключа,
	// соответствующую переданному индексу
	const PartOfUniqueAnswerOptionsKey &at(uint index) const;
	const PartOfUniqueAnswerOptionsKey &operator[](uint index) const;
	PartOfUniqueAnswerOptionsKey &operator[](uint index);

	/**
	 * @brief Метод возвращает индекс последнего вопроса
	 * @return индекс последнего вопроса
	 */
	uint getCurrentQuestionIndex() const;

	/**
	 * @brief Метод заменяет индекс текущего вопроса на переданный
	 * @param answerOptionIndex - индекс нового вопроса
	 */
	void replaceCurrentQuestionIndex(uint questionIndex);

	/**
	 * @brief Метод запоминает индекс нового вопроса
	 * @param questionIndex - индекс нового вопроса
	 */
	void addQuestion(uint questionIndex);

	/**
	 * @brief Метод добавляет индекс нового варианта ответа к последнему
	 * добавленному вопросу
	 * @param answerOptionIndex - индекс нового варианта ответа
	 */
	void addAnswerOptionToLastQuestion(uint answerOptionIndex);

	/**
	 * @brief Метод возвращает индексы вариантов ответов последнего добавленного
	 * вопроса
	 * @return индексы вариантов ответов
	 */
	Indexes getCurrentAnswerOptionIndexes() const;

	/**
	 * @brief Метод удаляет ответ с переданным индексом из текущего вопроса
	 * @param answerOptionIndex - индекс варианта ответа
	 */
	void deleteAnswerOptionFromCurrentQuestion(uint answerOptionIndex);

	/**
	 * @brief Метод заменяет варианты ответов для текущего вопроса
	 * @param answerOptionIndexes - индекс вариантов ответов
	 */
	void setAnswerOptionsForCurrentQuestion(const Indexes &answerOptionIndexes);

	/**
	 * @brief Метод удаляет из ключа все записи для вопроса с переданным
	 *        количеством баллов
	 * @param questionIndex - индекс вопроса
	 * @param points - количество баллов
	 */
	void deleteQuestion(uint questionIndex, uint points = 1);
};
