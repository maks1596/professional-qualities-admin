#pragma once

#include <QString>
#include <QException>

#include <string>
#include <exception>
using namespace std;

#include "Entities/AnswerOption/AnswerOption.h"

class ConnectionError : public exception {
public:
    const char * what() const noexcept {
        return "Check your internet connection";
    }
};

class IncorrectLoginOrPassword : public exception {
public:
    const char * what() const noexcept {
        return "Incorrect login or password";
    }
};

class TestNotFound : public exception {
public:
    const char * what() const noexcept {
        return "Test not found";
    }
};

class TestNotCreated : public exception {
public:
    const char * what() const noexcept {
        return "Test not created";
    }
};

class QuestionNotLoaded : public exception {
public:
    const char * what() const noexcept {
        return "Question not loaded";
    }
};

class UniqueAnswerOptionNotLoaded : public exception {
public:
    const char * what() const noexcept {
        return "Unique answer option not loaded";
    }
};

class GeneralAnswerOptionNotLoaded : public exception {
public:
    const char * what() const noexcept {
        return "General answer option not loaded";
    }
};

class ScaleNotLoaded : public exception {
public:
    const char * what() const noexcept {
        return "Scale not loaded";
    }
};

class TestAlreadyExists : public exception {
public:
    TestAlreadyExists(const QString &testName) :
        m_testName(testName) {}

    const char * what() const noexcept {
        return string("Test with name \"" + m_testName.toStdString() + "\" already exists").data();
    }

private:
    QString m_testName;
};

class TestAlreadyUsed : public exception {
public:
    TestAlreadyUsed(const QString &testName) :
        m_testName(testName) {}

    const char * what() const noexcept {
        return string("Test with name \"" + m_testName.toStdString() + "\" already used").data();
    }

private:
    QString m_testName;
};

class FileWithTestNotFound : public exception {
public:
    const char * what() const noexcept {
        return "File with test not found";
    }
};

class SettingGeneralAnswerOptionForQuestionsWithUniqueAnswerOptions : public exception {
public:
    const char * what() const noexcept {
        return "Setting general answer option for questions with unique answer options is not allowed";
    }
};

class SettingUniqueAnswerOptionForQuestionsWithGeneralAnswerOptions : public exception {
public:
    const char * what() const noexcept {
        return "Setting unique answer option for questions with general answer options is not allowed";
    }
};

class AnswerOptionTypeIsUndefined : public exception {
public:
    const char * what() const noexcept {
        return "It's imposible to set test key before declaration of base part of test";
    }
};

class InvalidQuestionNumber : public exception {
public:
    InvalidQuestionNumber(const QString &invalidNumber)
        : m_invalidNumber(invalidNumber) {}

    const char * what() const noexcept {
        return string("Invalid question number: \"" + m_invalidNumber.toStdString() + "\"").data();
    }

private:
    QString m_invalidNumber;
};

class InvalidAnswerOption : public exception {
public:
    InvalidAnswerOption(const AnswerOption &invalidAnswerOption)
        : m_invalidAnswerOption(invalidAnswerOption) {}

    const char * what() const noexcept {
        return string("Invalid answer option: \"" +
                      m_invalidAnswerOption.getFormulation().toStdString() +
                      "\"").data();
    }

private:
    AnswerOption m_invalidAnswerOption;
};

class QuestionNumberOutOfRange : public exception {
public:
    QuestionNumberOutOfRange(const uint &questionNumber)
        : m_questionNumber(questionNumber) {}

    const char * what() const noexcept {
        return string("Question number \"" +
                      QString::number(m_questionNumber).toStdString() +
                      "\" out of range").data();
    }

private:
    uint m_questionNumber;
};

class KeyScaleExpected : public exception {
public:
    const char * what() const noexcept {
        return "First row in key must be a scale\n"
               "May be you should remove semicolon after scale";
    }
};

class EvaluationMapScaleExpected : public exception {
public:
    const char * what() const noexcept {
        return "First row in evaluation map must be a scale\n"
               "May be you should remove semicolon after scale";
    }
};

class InvalidNumberOfPoints : public exception {
public:
    InvalidNumberOfPoints(const QString &numberOfPoints)
        : m_numberOfPoints(numberOfPoints) {}

    const char * what() const noexcept {
        return string("Invalid number of points: " + m_numberOfPoints.toStdString()).data();
    }
private:
    QString m_numberOfPoints;
};

class InvalidRange : public exception {
public:
    InvalidRange(const QString &range) : m_range(range) {}

    const char * what() const noexcept {
        return string("Invalid range: " + m_range.toStdString()).data();
    }
private:
    QString m_range;
};

class SettingUndefinedAnswerOptionsType : public exception {
public:
    const char * what() const noexcept {
        return "Setting undefined answer options type is not allowed.";
    }
};
