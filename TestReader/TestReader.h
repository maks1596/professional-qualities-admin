#pragma once

#include <QObject>
#include <QString>
#include <QTextStream>

#include "Entities/Test/Test.h"

/** @brief Конечный автомат для считывания теста из текстового файла
 */
class TestReader : public QObject {
Q_OBJECT

public:
    void readTest(const QString &fileName);

signals:
    void testRead(const Test &test);
    void error(const QString &err);
    void progress(const QString &message);

private:    
    inline QString pickTestName(const QString &fileName);
    inline QChar readSymbol();
    inline void instructionRead();
    inline void generalAnswerOptionRead();
    inline void questionRead();
    inline void uniqueAnswerOptionRead();
    inline void scaleRead();
    inline void tagRead();
    inline void argumentRead();
    inline void pointsRead();
    inline void lowerRangeValueRead();
    inline void upperRangeValueRead();
    inline void scaleResultRead();

    inline QString removeLastWord();
    inline QString pickLastWord() const;
    inline bool isNumber(const QString &str) const;

    enum State {
        WAIT_KEY_WORD,
        READ_INSTRUCTION,
        READ_GENERAL_ANSWER_OPTIONS,
        WAIT_QUESTION,
        READ_QUESTION,
        WAIT_UNIQUE_ANSWER_OPTION,
        READ_UNIQUE_ANSWER_OPTION,

        READ_KEY,
        READ_KEY_SCALE,
        READ_TAG,
        READ_ARGUMENTS,
        READ_POINTS,

        READ_EVALUATION_MAP,
        READ_EVALUATION_MAP_SCALE,
        READ_LOWER_RANGE_VALUE,
        READ_UPPER_RANGE_VALUE,
        READ_SCALE_RESULT,
        STOP
    };

    /**
     * @brief Метод обрабатывает текущее состояние конечного автомата
     *        для переданного символа и возвращает новое состояние
     * @param currentState - текущее состояние
     * @param currentSymbol - текущий символ
     * @return новое состояние конечного автомата
     */
    inline State handleState(State currentState, QChar currentSymbol);

    State waitKeyWord(QChar curSymbol);
    State readInstruction(QChar curSymbol);
    State readGeneralAnswerOptions(QChar curSymbol);

    State waitQuestion(QChar curSymbol);
    State readQuestion(QChar curSymbol);

    State waitUniqueAnswerOption(QChar curSymbol);
    State readUniqueAnswerOption(QChar curSymbol);

    State readKey(QChar curSymbol);
    State readKeyScale(QChar curSymbol);
    State readTag(QChar curSymbol);
    State readArguments(QChar curSymbol);
    State readPoints(QChar curSymbol);

    State readEvaluationMap(QChar curSymbol);
    State readEvaluationMapScale(QChar curSymbol);
    State readLowerRangeValue(QChar curSymbol);
    State readUpperRangeValue(QChar curSymbol);
    State readScaleResult(QChar curSymbol);

    const static QMap<QString, State> m_keyWordStates;

    Test m_resultTest;
    uint m_index = 0;
    QString m_fileContent;
    QString m_buffer;
    uint m_openBracesAmount = 0;
};
