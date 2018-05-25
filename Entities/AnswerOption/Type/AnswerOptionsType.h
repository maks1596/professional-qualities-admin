#pragma once

class QString;

enum AnswerOptionsType {
    UNDEFINED,
    UNIQUE,
    GENERAL
};

QString answerOptionsTypeToString(const AnswerOptionsType &answerOptionsType);
AnswerOptionsType answerOptionsTypeFromString(const QString &string);
