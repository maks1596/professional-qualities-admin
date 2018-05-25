#include "AnswerOptionsType.h"

#include <QString>

//  :: Constants ::

const QString GENERAL_ANSWER_OPTIONS_TYPE_STRING = "General";
const QString UNIQUE_ANSWER_OPTIONS_TYPE_STRING = "Unique";
const QString UNDEFINED_ANSWER_OPTIONS_TYPE_STRING = "Undefined";

//  :: Public functions ::

QString answerOptionsTypeToString(const AnswerOptionsType &answerOptionsType) {
    switch(answerOptionsType) {
	case GENERAL: return GENERAL_ANSWER_OPTIONS_TYPE_STRING;
	case UNIQUE: return UNIQUE_ANSWER_OPTIONS_TYPE_STRING;
	case UNDEFINED: return UNDEFINED_ANSWER_OPTIONS_TYPE_STRING;
    }
	return UNDEFINED_ANSWER_OPTIONS_TYPE_STRING;
}

AnswerOptionsType answerOptionsTypeFromString(const QString &string) {
	if (string == GENERAL_ANSWER_OPTIONS_TYPE_STRING) {
        return GENERAL;
	} else if (string == UNIQUE_ANSWER_OPTIONS_TYPE_STRING) {
        return UNIQUE;
    } else {
        return UNDEFINED;
    }
}
