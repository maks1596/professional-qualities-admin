#include "TestReader.h"

#include <QDebug>
#include <QFile>
#include <QStringList>

#include "Exception.h"

const QMap<QString, TestReader::State> TestReader::m_keyWordStates {
    {"Инструкция",       TestReader::READ_INSTRUCTION},
    {"Варианты ответов", TestReader::READ_GENERAL_ANSWER_OPTIONS},
    {"Вопросы",          TestReader::WAIT_QUESTION},
    {"Ключ",             TestReader::READ_KEY},
    {"Оценочная карта",  TestReader::READ_EVALUATION_MAP}
};

void TestReader::readTest(const QString &fileName) {
    try {
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly)) {
            emit error(FileWithTestNotFound().what());
        }

        QTextStream fileStream(&file);
        m_fileContent = fileStream.readAll();
        file.close();

        m_index = m_openBracesAmount = 0;
        m_resultTest = move(Test());
        m_resultTest.setName(pickTestName(fileName));
        State state = WAIT_KEY_WORD;
        while(state != STOP) {
            state = handleState(state, readSymbol());
        }

        emit testRead(move(m_resultTest));
    } catch(const exception &ex) {
        emit error(ex.what());
    }
}

TestReader::State TestReader::handleState(State currentState, QChar currentSymbol) {
	switch (currentState) {
    case WAIT_KEY_WORD:                 return waitKeyWord(currentSymbol);
    case READ_INSTRUCTION:              return readInstruction(currentSymbol);

    case READ_GENERAL_ANSWER_OPTIONS:   return readGeneralAnswerOptions(currentSymbol);

    case WAIT_QUESTION:                 return waitQuestion(currentSymbol);
    case READ_QUESTION:                 return readQuestion(currentSymbol);

    case WAIT_UNIQUE_ANSWER_OPTION:     return waitUniqueAnswerOption(currentSymbol);
	case READ_UNIQUE_ANSWER_OPTION:     return readUniqueAnswerOption(currentSymbol);

	case READ_KEY:                      return readKey(currentSymbol);
	case READ_KEY_SCALE:                return readKeyScale(currentSymbol);
	case READ_TAG:                      return readTag(currentSymbol);
	case READ_ARGUMENTS:                return readArguments(currentSymbol);
	case READ_POINTS:                   return readPoints(currentSymbol);

	case READ_EVALUATION_MAP:           return readEvaluationMap(currentSymbol);
	case READ_EVALUATION_MAP_SCALE:     return readEvaluationMapScale(currentSymbol);
	case READ_LOWER_RANGE_VALUE:        return readLowerRangeValue(currentSymbol);
	case READ_UPPER_RANGE_VALUE:        return readUpperRangeValue(currentSymbol);
	case READ_SCALE_RESULT:             return readScaleResult(currentSymbol);

	case STOP:                          return currentState;
    }

    return STOP;
}

inline
QString TestReader::pickTestName(const QString &fileName) {
    int slashIdx = fileName.lastIndexOf('/');
    if(slashIdx < 0) { slashIdx = 0; }

    int dotIdx = fileName.lastIndexOf('.');
    if(dotIdx < 0 || dotIdx < slashIdx) {
        dotIdx = fileName.size();
    }

    QString result(fileName);
    result.remove(0, slashIdx + 1)
          .remove(dotIdx - slashIdx - 1, result.size());
    return result;
}

// При большом желании можно напрямую читать из файла
// Но тогда нужно не забыть сказать "Привет!" кодировкам
QChar TestReader::readSymbol() {
    return m_fileContent[m_index++];
}

TestReader::State TestReader::waitKeyWord(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case 0: return STOP;
    case '\r':
    case '\n': {
        m_buffer.clear();
    } break;
    case ':': {
		qDebug() << "Buffer = " << m_buffer;
        State result = m_keyWordStates.value(m_buffer.simplified(),
                                             WAIT_KEY_WORD);
        m_buffer.clear();
        return result;
    } break;
    default: {
        m_buffer += curSymbol;
    } break;
    }
    return WAIT_KEY_WORD;
}

// Инструкция будет читаться до двойного перехода на новую строку
// Все одиночные переходы на новую строку заменяются пробелами
TestReader::State TestReader::readInstruction(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case '\0':  {
        instructionRead();
        return STOP;
    } break;
    case '\r': {
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return readInstruction(curSymbol);
        case '\r': {
            instructionRead();
            return WAIT_KEY_WORD;
        } break;
        case '\n': {
        // Время заморочиться с двусимвольным переходом на новую строку в винде
            curSymbol = readSymbol();
            switch(curSymbol.unicode()) {
            case '\0': return readInstruction(curSymbol);
            case '\r': {
                readSymbol();   // Прочитали '\n'
                instructionRead();
                return WAIT_KEY_WORD;
            } break;
            }
        } break;
        }
        m_buffer += ' ' + curSymbol;
    } break;
    case '\n': {
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return readInstruction(curSymbol);
        case '\n': {
            instructionRead();
            return WAIT_KEY_WORD;
        } break;
        }
        m_buffer += ' ' + curSymbol;
    } break;
    default: {
        m_buffer += curSymbol;
    } break;
    }
    return READ_INSTRUCTION;
}

void TestReader::instructionRead() {
    m_resultTest.setInstruction(m_buffer.simplified());
    m_buffer.clear();
}

// Варианты ответов разделяются ',', ';' или новой строкой
TestReader::State TestReader::readGeneralAnswerOptions(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case '\0': {
        generalAnswerOptionRead();
        return STOP;
    } break;
    case '\r': {
        generalAnswerOptionRead();
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\r': return WAIT_KEY_WORD;
        case '\n': {
            curSymbol = readSymbol();
            switch (curSymbol.unicode()) {
            case '\r': {
                readSymbol();   // Игнорируем '\n'
                return WAIT_KEY_WORD;
            } break;
            case '\0': {
                return STOP;
            } break;
            }
        } break;
        }
        m_buffer = curSymbol;
    } break;
    case '\n': {
        generalAnswerOptionRead();
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\n': return WAIT_KEY_WORD;
        }
        m_buffer = curSymbol;
    } break;
    case ',':
    case ';': {
        generalAnswerOptionRead();
    } break;
    default: {
        m_buffer += curSymbol;
    } break;
    }
    return READ_GENERAL_ANSWER_OPTIONS;
}

void TestReader::generalAnswerOptionRead() {
    m_resultTest.addGeneralAnswerOption(m_buffer.simplified());
    m_buffer.clear();
}

// Вопрос должен начинаться строго с "число."
TestReader::State TestReader::waitQuestion(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case '\0': return STOP;
    case '\r': {
        m_buffer.clear();
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\r': return WAIT_KEY_WORD;
        case '\n': {
            curSymbol = readSymbol();
            switch(curSymbol.unicode()) {
            case '\0': return STOP;
            case '\r': {
                readSymbol();
                return WAIT_KEY_WORD;
            } break;
            }
        } break;
        }
    } break;
    case '\n': {
        m_buffer.clear();
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\n': return WAIT_KEY_WORD;
        }
    } break;
    case '.': {
        if(isNumber(m_buffer)) {
            m_buffer.clear();
            return READ_QUESTION;
        }
    } break;
    }
    m_buffer += curSymbol;
    return WAIT_QUESTION;
}

TestReader::State TestReader::readQuestion(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case '\0': {
        questionRead();
        return STOP;
    } break;
    case '\r': {
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return readQuestion(curSymbol);
        case '\r': {
            questionRead();
            return WAIT_KEY_WORD;
        } break;
        case '\n': {
            curSymbol = readSymbol();
            switch(curSymbol.unicode()) {
            case '\0': return readQuestion(curSymbol);
            case '\r': {
                readSymbol();
                questionRead();
                return WAIT_KEY_WORD;
            } break;
            }
        } break;
        }
        m_buffer += ' ';
    } break;
    case '\n': {
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return readQuestion(curSymbol);
        case '\n': {
            questionRead();
            return WAIT_KEY_WORD;
        } break;
        }
        m_buffer += ' ';
    } break;
    case '(': ++m_openBracesAmount; break;
    case ')': {
        if(m_openBracesAmount) {
           --m_openBracesAmount;
        } else {
            removeLastWord();
            questionRead();
            return READ_UNIQUE_ANSWER_OPTION;
        }
    } break;
    case '.': {
        if(isNumber(pickLastWord())) {
            removeLastWord();
            questionRead();
            return READ_QUESTION;
        }
    } break;
    }
    m_buffer += curSymbol;
    return READ_QUESTION;
}

void TestReader::questionRead() {
    m_resultTest.addQuestion(m_buffer.simplified());
    m_buffer.clear();
}


TestReader::State TestReader::waitUniqueAnswerOption(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case '\0': return STOP;
    case '\r': {
        m_buffer.clear();
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\r': return WAIT_KEY_WORD;
        case '\n': {
            curSymbol = readSymbol();
            switch(curSymbol.unicode()) {
            case '\0': return STOP;
            case '\r': {
                readSymbol();
                m_buffer.clear();
                return WAIT_KEY_WORD;
            } break;
            }
        } break;
        }
    } break;
    case '\n': {
        m_buffer.clear();
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\n': return WAIT_KEY_WORD;
        }
    } break;
    case '(': ++m_openBracesAmount; break;
    case ')': {
        if(m_openBracesAmount) {
            --m_openBracesAmount;
        } else {
            m_buffer.clear();
            return READ_UNIQUE_ANSWER_OPTION;
        }
    } break;
    case '.': {
        if(isNumber(pickLastWord())) {
            m_buffer.clear();
            return READ_QUESTION;
        }
    } break;
    }
    m_buffer += curSymbol;
    return WAIT_UNIQUE_ANSWER_OPTION;
}

TestReader::State TestReader::readUniqueAnswerOption(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case '\0': {
        uniqueAnswerOptionRead();
        return STOP;
    } break;
    case '\r': {
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return readUniqueAnswerOption(curSymbol);
        case '\r': {
            uniqueAnswerOptionRead();
            return WAIT_KEY_WORD;
        } break;
        case '\n': {
            curSymbol = readSymbol();
            switch(curSymbol.unicode()) {
            case '\0': return readUniqueAnswerOption(curSymbol);
            case '\r': {
                readSymbol();
                uniqueAnswerOptionRead();
                return WAIT_KEY_WORD;
            } break;
            }
        } break;
        }
        m_buffer += ' ';
    } break;
    case '\n': {
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return readUniqueAnswerOption(curSymbol);
        case '\n': {
            uniqueAnswerOptionRead();
            return WAIT_KEY_WORD;
        } break;
        }
        m_buffer += ' ';
    } break;
    case '(': ++m_openBracesAmount; break;
    case ')': {
        if(m_openBracesAmount) {
            --m_openBracesAmount;
        } else {
            removeLastWord();
            uniqueAnswerOptionRead();
            return WAIT_UNIQUE_ANSWER_OPTION;
        }
    } break;
    case '.': {
        if(isNumber(pickLastWord())) {
            removeLastWord();
            uniqueAnswerOptionRead();
            return READ_QUESTION;
        }
    }
    case ',':
    case ';': {
        uniqueAnswerOptionRead();
        return WAIT_UNIQUE_ANSWER_OPTION;
    } break;
    }
    m_buffer += curSymbol;
    return READ_UNIQUE_ANSWER_OPTION;
}

void TestReader::uniqueAnswerOptionRead() {
    m_resultTest.addAnswerOptionToLastQuestion(m_buffer.simplified());
    m_buffer.clear();
}

QString TestReader::removeLastWord() {
    QString tmp = pickLastWord();
    m_buffer.remove(m_buffer.lastIndexOf(' '), m_buffer.size());
    return tmp;
}

QString TestReader::pickLastWord() const {
    return m_buffer.split(' ').back();
}

bool TestReader::isNumber(const QString &str) const {
    bool ok;
    str.toUInt(&ok);
    return ok;
}

// Просто ожидаем конца строки
TestReader::State TestReader::readKey(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case '\0': return STOP;
    case '\r': {
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\r': return WAIT_KEY_WORD;
        case '\n': {
            curSymbol = readSymbol();
            switch(curSymbol.unicode()) {
            case '\0': return STOP;
            case '\r': {
                readSymbol();   // Прочли '\n'
                return WAIT_KEY_WORD;
            } break;
            }
        } break;
        }
        m_buffer = curSymbol;
        return READ_KEY_SCALE;
    } break;
    case '\n': {
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\n': return WAIT_KEY_WORD;
        }
        m_buffer = curSymbol;
        return READ_KEY_SCALE;
    } break;
    }
    return READ_KEY;
}

// Читаем качество до конца строки
TestReader::State TestReader::readKeyScale(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case '\0': {
        scaleRead();
        return STOP;
    } break;
    case '\r': {
        scaleRead();
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\r': return WAIT_KEY_WORD;
        case '\n': {
            curSymbol = readSymbol();
            switch(curSymbol.unicode()) {
            case '\0': return STOP;
            case '\r': {
                readSymbol();   // Прочли '\n'
                return WAIT_KEY_WORD;
            } break;
            }
        } break;
        }
        m_buffer = curSymbol;
        return READ_TAG;
    } break;
    case '\n': {
        scaleRead();
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\n': return WAIT_KEY_WORD;
        }
        m_buffer = curSymbol;
        return READ_TAG;
    } break;
    case ':': {
        if(m_resultTest.hasOnlyOneScale()) {
            return readTag(curSymbol);
        } else {
            throw KeyScaleExpected();
        }
    } break;
    }
    m_buffer += curSymbol;
    return READ_KEY_SCALE;
}

void TestReader::scaleRead() {
    m_resultTest.toScale(m_buffer.simplified());
    m_buffer.clear();
}

// Тэг всгда должен заканчиваться двоеточием
TestReader::State TestReader::readTag(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case '\0':
    case '\r':
    case '\n': return readKeyScale(curSymbol);
    case ':': {
        tagRead();
        return READ_ARGUMENTS;
    } break;
    }
    m_buffer += curSymbol;
    return READ_TAG;
}

void TestReader::tagRead() {
    // В буфере лежит либо вариант ответа, либо номер вопроса
    m_buffer = m_buffer.simplified();
    switch(m_resultTest.getAnswerOptionsType()) {
    case GENERAL: { // => буфер = вариант ответа
        m_resultTest.addAnswerOptionToCurrentScale(m_buffer);
    } break;
    case UNIQUE: {  // => буфер = номер вопроса
        if(isNumber(m_buffer)) {
            m_resultTest.addQuestionToCurrentScale(m_buffer.toUInt());
        } else {
            throw InvalidQuestionNumber(m_buffer);
        }
    } break;
    case UNDEFINED: {
        throw AnswerOptionTypeIsUndefined();
    }
    }
    m_buffer.clear();
}

TestReader::State TestReader::readArguments(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case '\0': {
        argumentRead();
        return STOP;
    } break;
    case '\r': {
        argumentRead();
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\r': return WAIT_KEY_WORD;
        case '\n': {
            curSymbol = readSymbol();
            switch (curSymbol.unicode()) {
            case '\0': return STOP;
            case '\r': {
                readSymbol();   // Игнорируем '\n'
                return WAIT_KEY_WORD;
            } break;
            }
        } break;
        }
        m_buffer = curSymbol;
        return READ_TAG;
    } break;
    case '\n': {
        argumentRead();
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\n': return WAIT_KEY_WORD;
        }
        m_buffer = curSymbol;
        return READ_TAG;
    } break;
    case ',':
    case ';': {
        argumentRead();
    } break;
    case '=': {
        argumentRead();
        return READ_POINTS;
    }
    default: {
        m_buffer += curSymbol;
    } break;
    }
    return READ_ARGUMENTS;
}

void TestReader::argumentRead() {
    // Схема аналогична tagRead(). Только case-ы переставлены
    // В буфере лежит либо вариант ответа, либо номер вопроса
    m_buffer = m_buffer.simplified();
    switch(m_resultTest.getAnswerOptionsType()) {
    case UNIQUE: { // => буфер = вариант ответа
        m_resultTest.addAnswerOptionToCurrentScale(m_buffer);
    } break;

    case GENERAL: {  // => буфер = номер вопроса
        if(isNumber(m_buffer)) {
            m_resultTest.addQuestionToCurrentScale(m_buffer.toUInt());
        } else {
            throw InvalidQuestionNumber(m_buffer);
        }
    } break;

    case UNDEFINED: {
        throw AnswerOptionTypeIsUndefined();
    }
    }
    m_buffer.clear();
}

// Читаем до конца строки
TestReader::State TestReader::readPoints(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case '\0': {
        pointsRead();
        return STOP;
    } break;
    case '\r': {
        pointsRead();
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\r': return WAIT_KEY_WORD;
        case '\n': {
            curSymbol = readSymbol();
            switch (curSymbol.unicode()) {
            case '\0': return STOP;
            case '\r': {
                readSymbol();   // Игнорируем '\n'
                return WAIT_KEY_WORD;
            } break;
            }
        } break;
        }
        m_buffer = curSymbol;
        return READ_TAG;
    } break;
    case '\n': {
        pointsRead();
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\n': return WAIT_KEY_WORD;
        }
        m_buffer = curSymbol;
        return READ_TAG;
    } break;
    default: {
        m_buffer += curSymbol;
    } break;
    }
    return READ_POINTS;
}

void TestReader::pointsRead() {
    m_buffer = m_buffer.trimmed();
    bool ok;
    int points = m_buffer.toInt(&ok);
    if(ok) {
        m_resultTest.setPointsToCurrentScale(points);
    } else {
        throw InvalidNumberOfPoints(m_buffer);
    }
	m_buffer.clear();
}

// Аналогично ситуации с чтением ключа - читаем до конца строки
TestReader::State TestReader::readEvaluationMap(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case '\0': return STOP;
    case '\r': {
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\r': return WAIT_KEY_WORD;
        case '\n': {
            curSymbol = readSymbol();
            switch(curSymbol.unicode()) {
            case '\0': return STOP;
            case '\r': {
                readSymbol();   // Прочли '\n'
                return WAIT_KEY_WORD;
            } break;
            }
        } break;
        }
        m_buffer = curSymbol;
        return READ_EVALUATION_MAP_SCALE;
    } break;
    case '\n': {
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\n': return WAIT_KEY_WORD;
        }
        m_buffer = curSymbol;
        return READ_EVALUATION_MAP_SCALE;
    } break;
    }
    return READ_EVALUATION_MAP;
}

TestReader::State TestReader::readEvaluationMapScale(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case '\0': {
        scaleRead();
        return STOP;
    } break;
    case '\r': {
        scaleRead();
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\r': return WAIT_KEY_WORD;
        case '\n': {
            curSymbol = readSymbol();
            switch(curSymbol.unicode()) {
            case '\0': return STOP;
            case '\r': {
                readSymbol();   // Прочли '\n'
                return WAIT_KEY_WORD;
            } break;
            }
        } break;
        }
        m_buffer = curSymbol;
        return READ_LOWER_RANGE_VALUE;
    } break;
    case '\n': {
        scaleRead();
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\n': return WAIT_KEY_WORD;
        }
        m_buffer = curSymbol;
        return READ_LOWER_RANGE_VALUE;
    } break;
    case ':': {
        if(m_resultTest.hasOnlyOneScale()) {
            return readLowerRangeValue(curSymbol);
        } else {
            throw EvaluationMapScaleExpected();
        }
    } break;
    }
    m_buffer += curSymbol;
    return READ_EVALUATION_MAP_SCALE;
}

TestReader::State TestReader::readLowerRangeValue(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case '\0':
    case '\r':
    case '\n': return readEvaluationMapScale(curSymbol);
    case '-': {
        // Пока продолжим читать
        m_buffer += curSymbol;
        return READ_UPPER_RANGE_VALUE;
    } break;
    case ':': {
        lowerRangeValueRead();
        return READ_SCALE_RESULT;
    } break;
    }
    m_buffer += curSymbol;
    return READ_LOWER_RANGE_VALUE;
}

void TestReader::lowerRangeValueRead() {
    m_buffer = m_buffer.trimmed();
    if(isNumber(m_buffer)) {
        m_resultTest.addRangeToCurrentScale(m_buffer.toUInt());
        m_buffer.clear();
    } else {
        throw InvalidNumberOfPoints(m_buffer);
    }
}

TestReader::State TestReader::readUpperRangeValue(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case '\0':
    case '\r':
    case '\n': return readEvaluationMapScale(curSymbol);
    case ':': {
        upperRangeValueRead();
        return READ_SCALE_RESULT;
    } break;
    }
    m_buffer += curSymbol;
    return READ_UPPER_RANGE_VALUE;
}

// В буфере лежат два беззнаковых числа, разделённых '-'
void TestReader::upperRangeValueRead() {
    auto rangeValues = m_buffer.split('-');
    if(rangeValues.size() == 2) {
        rangeValues.front() = rangeValues.front().trimmed();
        rangeValues.back() = rangeValues.back().trimmed();
        if(isNumber(rangeValues.front())) {
            if(isNumber(rangeValues.back())) {
                m_resultTest.addRangeToCurrentScale(rangeValues.front().toUInt(),
                                                       rangeValues.back().toUInt());
                m_buffer.clear();
            } else { throw InvalidNumberOfPoints(rangeValues.back()); }
        } else { throw InvalidNumberOfPoints(rangeValues.front()); }
    } else { throw InvalidRange(m_buffer); }
}

TestReader::State TestReader::readScaleResult(QChar curSymbol) {
    switch(curSymbol.unicode()) {
    case '\0': {
        scaleResultRead();
        return STOP;
    } break;
    case '\r': {
        scaleResultRead();
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\r': return WAIT_KEY_WORD;
        case '\n': {
            curSymbol = readSymbol();
            switch(curSymbol.unicode()) {
            case '\0': return STOP;
            case '\r': {
                readSymbol();   // Прочли '\n'
                return WAIT_KEY_WORD;
            } break;
            }
        } break;
        }
        m_buffer = curSymbol;
        return READ_LOWER_RANGE_VALUE;
    } break;
    case '\n': {
        scaleResultRead();
        curSymbol = readSymbol();
        switch(curSymbol.unicode()) {
        case '\0': return STOP;
        case '\n': return WAIT_KEY_WORD;
        }
        m_buffer = curSymbol;
        return READ_LOWER_RANGE_VALUE;
    } break;
    }
    m_buffer += curSymbol;
    return READ_SCALE_RESULT;
}

void TestReader::scaleResultRead() {
    m_resultTest.setResultToCurrentScale(m_buffer.simplified());
    m_buffer.clear();
}
