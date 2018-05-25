#ifndef TEST_H
#define TEST_H

#include <QList>
#include <QObject>
#include <QString>

#include "AnswerOptionsType/AnswerOptionsType.h"
#include "Question.h"
#include "Scale.h"
#include "Serializable/Serializable.h"

class AnswerOption;

/** @brief Временный посредник между файлами с тестами и БД \
 *         Нужен для отладки алгоритмов считывания тестов из файлов
 */
class Test : public Serializable {
public:
    Test(const int id = 0) : m_id(id) {}

    Test(const Test &other) = default;
    Test(Test &&other) = default;
    Test& operator=(Test &&other) = default;

    int getID() const;
    void setID(const int &id);

    QString getName() const;
    void setName(const QString &name);

    QString getInstruction() const;
    void setInstruction(const QString &instruction);

    AnswerOptionsType getAnswerOptionsType() const;
    void setAnswerOptionsType(const AnswerOptionsType &type);

    Questions getQuestions() const;
    Questions *getQuestions();
    void addQuestion(const QString &formulation);
    void addQuestion(Question *question);

    AnswerOptions getAnswerOptions() const;
    AnswerOptions *getAnswerOptions();
    void addAnswerOptionToAll(const AnswerOption &answerOption);
    void addAnswerOptionToLastQuestion(const AnswerOption &answerOption);

    Scales *getScales();
    void toScale(const QString &scale);
    bool hasOnlyOneScale();
    void addAnswerOptionToCurrentScale(const AnswerOption &answerOption);
    void addQuestionToCurrentScale(const uint &questionNumber);
    void setPointsToCurrentScale(const int &numberOfPoints);

    void addRangeToCurrentScale(const uint &lower/*, upper = lower*/);
    void addRangeToCurrentScale(const uint &lower, const uint &upper);
    void setResultToCurrentScale(const QString &result);

    //  :: Serializable ::
    virtual QJsonObject toJsonObject() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

private:
    void addAnswerOptionFromContainer(const AnswerOption &answerOption,
                                      const AnswerOptions &con);
    uint parseToAnswerOption(const AnswerOption &src,
                             const AnswerOptions &con);

    int m_id;
    QString m_name;
    QString m_instruction;
    AnswerOptionsType m_answerOptionsType = UNDEFINED;
    AnswerOptions m_answerOptions;
    Questions m_questions;
    Scales m_scales;
    Scales::iterator m_curScale;
};

#endif // TEST_H
