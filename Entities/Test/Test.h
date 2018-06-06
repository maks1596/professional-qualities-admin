#pragma once

#include <QList>
#include <QObject>
#include <QScopedPointer>
#include <QString>

#include "Entities/AnswerOption/Type/AnswerOptionsType.h"
#include "Entities/Question/Question.h"
#include "Entities/Scale/Scale.h"
#include "Entities/ShortTestInfo/ShortTestInfo.h"

class AnswerOption;

/** @brief Временный посредник между файлами с тестами и БД
 *         Нужен для отладки алгоритмов считывания тестов из файлов
 */
class Test : public ShortTestInfo {
public:
	//  :: Lifecycle ::
	Test(int id = 0, const QString &name = "");

	//  :: Copy ::
	Test(const Test &other);
	Test &operator=(const Test &other);

	//  :: Move ::
	Test(Test &&other);
	Test &operator=(Test &&other);

	//  :: Destructor ::
	virtual ~Test() noexcept override;

	//  :: Accessors ::
    QString getInstruction() const;
    void setInstruction(const QString &instruction);

    AnswerOptionsType getAnswerOptionsType() const;
    void setAnswerOptionsType(const AnswerOptionsType &type);

	const Questions &getQuestions() const;
    Questions *getQuestions();
	void setQuestions(const Questions &questions);

    AnswerOptions getGeneralAnswerOptions() const;
    AnswerOptions *getGeneralAnswerOptions();
	void setGeneralAnswerOptions(const AnswerOptions &answerOptions);

    Scales *getScales();
	const Scales &getScales() const;
	void setScales(const Scales &scales);

	//  --------------------------------------------------
	//  :: Questions ::
	/**
	 * @brief Метод добавляет вопрос к сохранённым
	 * @param question - новый вопрос
	 */
	void addQuestion(const Question &question);

	//  :: Answer options ::
	/**
	 * @brief Метод добавляет общий вариант ответа к сохранённым
	 * @param answerOption - новый общий вариант ответа
	 */
	void addGeneralAnswerOption(const AnswerOption &answerOption);

	/**
	 * @brief Метод добавляет вариант ответа к посленему вопросу
	 * @param answerOption - вариант ответа
	 */
	void addAnswerOptionToLastQuestion(const AnswerOption &answerOption);

	//  :: Scales ::
	/**
	 * @brief Метод заменяет текущую шкалу на переданную
	 * @param scale - шкала, которую необходимо сделать текущей
	 */
	void toScale(const Scale &scale);

	//  :: Key  ::
	/**
	 * @brief Метод добавляет вариант ответа к ключу в текущей шкале
	 * @param answerOption - вариант ответа
	 */
	void addAnswerOptionToCurrentScale(const AnswerOption &answerOption);

	/**
	 * @brief Метод добавляет номер вопроса к ключу в текущей шкале
	 * @param questionNumber - номер вопроса
	 */
	void addQuestionToCurrentScale(const uint &questionNumber);

	/**
	 * @brief Метод устанавливает баллы для ключа текущей шкалы
	 * @param numberOfPoints
	 */
	void setPointsToCurrentScale(const int &numberOfPoints);

	//  :: Evaluation map
	/**
	 * @brief Метод добавляет диапазон к оценочной карте в текущей шкале
	 * @param lower - нижняя граница (она же верхняя) граница диапазона
	 */
	void addRangeToCurrentScale(const uint &lower/*, upper = lower*/);

	/**
	 * @brief Метод добавляет диапазон к оценочной карте в текущей шкале
	 * @param lower - нижняя ганица диапазона
	 * @param upper - верзхняя граница диапазона
	 */
	void addRangeToCurrentScale(const uint &lower, const uint &upper);

	/**
	 * @brief Метод устанавливает результат для последнего диапазона в оценочной
	 * карте текущей шкалы
	 * @param result - результат диапазона
	 */
	void setResultToCurrentScale(const QString &result);

    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	//  :: Accessors ::
	int getCurrentScaleIndex() const;
	void setCurrentScaleIndex(int index);

	/**
	 * @brief Метод добавляет к текущей шкале вариант ответа
	 * @param answerOption - вариант ответа
	 * @param container - известные на данный момент варианты ответа
	 */
    void addAnswerOptionFromContainer(const AnswerOption &answerOption,
									  const AnswerOptions &container);

	/**
	 * @brief Методы возвращают ссылку на текущую шкалу
	 * @return ссылка на текущую шкалу
	 */
	Scale &getCurrentScale();
	const Scale &getCurrentScale() const;

	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
