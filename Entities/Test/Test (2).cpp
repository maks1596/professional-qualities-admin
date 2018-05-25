#include "Test.h"

#include "QJsonArray"

#include "Exception.h"

const QString RUS_ALPHABETIC = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
const QString ENG_ALPHABETIC = "abcdefghijklmnopqrstuvwxyz";

//  :: Accessors ::
//  :: ID ::
int Test::getID() const {
    return m_id;
}
void Test::setID(const int &id) {
    m_id = id;
}

//  :: Name ::
QString Test::getName() const {
    return m_name;
}
void Test::setName(const QString &name) {
    m_name = name;
}

//  :: Instruction ::
QString Test::getInstruction() const {
    return m_instruction;
}
void Test::setInstruction(const QString &instruction) {
    m_instruction = instruction;
}

//  :: Questions ::
Questions Test::getQuestions() const {
    return m_questions;
}
Questions *Test::getQuestions() {
    return &m_questions;
}
void Test::addQuestion(const QString &formulation) {
    Question question;
    question.setFormulation(formulation);
    m_questions.append(move(question));
}

//  :: AnswerOptions ::
AnswerOptionsType Test::getAnswerOptionsType() const {
    return m_answerOptionsType;
}
void Test::setAnswerOptionsType(const AnswerOptionsType &type) {
    if(type != UNDEFINED) {
        m_answerOptionsType = type;
    } else {
        throw SettingUndefinedAnswerOptionsType();
    }
}

AnswerOptions Test::getAnswerOptions() const {
    return m_answerOptions;
}
AnswerOptions* Test::getAnswerOptions() {
    return &m_answerOptions;
}

void Test::addAnswerOptionToAll(const AnswerOption &answerOption) {
    switch(m_answerOptionsType) {
    case UNDEFINED: {
        m_answerOptionsType = GENERAL;
    }
    case GENERAL: {
        if(answerOption.isEmpty()) return;
        m_answerOptions.append(answerOption);
    } break;
    case UNIQUE: {
        throw SettingGeneralAnswerOptionForQuestionsWithUniqueAnswerOptions();
    } break;
    }

}

void Test::addAnswerOptionToLastQuestion(const AnswerOption &answerOption) {
    switch(m_answerOptionsType) {
    case UNDEFINED: {
        m_answerOptionsType = UNIQUE;
    }
    case UNIQUE: {
        if(answerOption.isEmpty()) return;
        m_questions.back().addAnswerOption(answerOption);
    } break;
    case GENERAL: {
        throw SettingUniqueAnswerOptionForQuestionsWithGeneralAnswerOptions();
    } break;
    }
}

//  :: Scales ::
Scales *Test::getScales() {
    return &m_scales;
}

void Test::toScale(const QString &scale) {
    m_curScale = find_if(m_scales.begin(), m_scales.end(),
                            [&](const Scale &cur)
                            { return cur.getName() == scale; });
    if(m_curScale == m_scales.end()) {
        m_scales.append(Scale(scale));
        m_curScale = m_scales.end() - 1;
    }
}

bool Test::hasOnlyOneScale() {
    return (m_scales.size() == 1);
}

void Test::addAnswerOptionToCurrentScale(const AnswerOption &answerOption) {
    if(answerOption.isEmpty()) return;

    switch(m_answerOptionsType) {
    case UNIQUE: {
        uint curQuestionIndex = m_curScale->getCurrentQuestionIndex();
        Question question = m_questions.at(curQuestionIndex);
        addAnswerOptionFromContainer(answerOption, *question.getAnswerOptions());
    } break;

    case GENERAL: {
        addAnswerOptionFromContainer(answerOption, m_answerOptions);
    } break;

    case UNDEFINED: break;
    }
}

void Test::addQuestionToCurrentScale(const uint &questionNumber) {
    uint questionIndex = questionNumber - 1;
    if(questionIndex < (uint)m_questions.size()) {
        switch(m_answerOptionsType) {
        case GENERAL: {
            m_curScale->addQuestionToLastAnswerOption(questionIndex);
        } break;
        case UNIQUE: {
            m_curScale->addQuestion(questionIndex);
        } break;
        case UNDEFINED: break;
        }
    } else {
        throw QuestionNumberOutOfRange(questionNumber);
    }
}

void Test::setPointsToCurrentScale(const int &points) {
    m_curScale->setPoints(points);
}

void Test::addRangeToCurrentScale(const uint &lower/*, upper = lower*/) {
    addRangeToCurrentScale(lower, lower);
}
void Test::addRangeToCurrentScale(const uint &lower, const uint &upper) {
    m_curScale->addAppraisedRange({lower, upper});
}

void Test::setResultToCurrentScale(const QString &result) {
    m_curScale->setResultToLastRange(result);
}

//  :: Serializable ::

QJsonObject Test::toJsonObject() const {
    QJsonObject result;

    result["id"] = m_id;
    result["name"] = m_name;
    result["instruction"] = m_instruction;
    result["answerOptionsType"] = answerOptionsTypeToString(m_answerOptionsType);

    QJsonArray jsonAnswerOptions;
    for (const auto &answerOption : m_answerOptions) {
        jsonAnswerOptions.append(answerOption.toJsonObject());
    }
    result["answerOptions"] = jsonAnswerOptions;

    QJsonArray jsonQuestions;
    for (const auto &question : m_answerOptions) {
        jsonQuestions.append(question.toJsonObject());
    }
    result["questions"] = jsonQuestions;

    QJsonArray jsonScales;
    for (const auto &scale : m_scales) {
        jsonScales.append(scale.toJsonObject());
    }
    result["scales"] = jsonScales;

    return result;
}

void Test::initWithJsonObject(const QJsonObject &json) {
    if (json.contains("id") && json["id"].isDouble()) {
        m_id = json["id"].toInt();
    }
    if (json.contains("name") && json["name"].isString()) {
        m_name = json["name"].toString();
    }
    if (json.contains("instruction") && json["instruction"].isString()) {
        m_instruction = json["instruction"].toString();
    }
    if (json.contains("answerOptionsType") && json["answerOptionsType"].isString()) {
        auto answerOptionsTypeString = json["answerOptionsType"].toString();
        m_answerOptionsType = answerOptionsTypeFromString(answerOptionsTypeString);
    }

    if (json.contains("answerOptions") && json["answerOptions"].isArray()) {
        auto jsonAnswerOptions = json["answerOptions"].toArray();
        m_answerOptions.clear();
        AnswerOption answerOption;

        for (const auto &jsonAnswerOption : jsonAnswerOptions) {
            answerOption.initWithJsonObject(jsonAnswerOption.toObject());
            m_answerOptions.append(answerOption);
        }
    }

    if (json.contains("questions") && json["questions"].isArray()) {
        auto jsonQuestions = json["questions"].toArray();
        m_questions.clear();
        Question question;

        for (const auto &jsonQuestion : jsonQuestions) {
            question.initWithJsonObject(jsonQuestion.toObject());
            m_questions.append(question);
        }
    }

    if (json.contains("scales") && json["scales"].isArray()) {
        auto jsonScales = json["scales"].toArray();
        m_scales.clear();
        Scale scale;

        for (const auto &jsonScale : jsonScales) {
            scale.initWithJsonObject(jsonScale.toObject());
            m_scales.append(scale);
        }
    }
}

//  :: Private ::

void Test::addAnswerOptionFromContainer(const AnswerOption &answerOption,
                                        const AnswerOptions &con) {
    int answerOptionIndex = con.indexOf(answerOption);
    if (answerOptionIndex < 0) {
        answerOptionIndex = parseToAnswerOption(answerOption, con);
    }

    switch(m_answerOptionsType) {
    case UNIQUE: {
        m_curScale->addAnswerOptionToLastQuestion(answerOptionIndex);
    } break;
    case GENERAL: {
        m_curScale->addAnswerOption(answerOptionIndex);
    } break;
    case UNDEFINED: break;
    }
}

inline
uint Test::parseToAnswerOption(const AnswerOption &src,
                               const AnswerOptions &con) {
    auto formulation = src.getFormulation();
    bool ok;    // Возможно в строке номер ответа
    int index = formulation.toUInt(&ok) - 1;
    if(!ok && formulation.size() == 1) {
        // Может там буква ответа. а, б или в, например
        index = RUS_ALPHABETIC.indexOf(formulation[0].toLower());
        if(index < 0) {
            // Может английская буква
            index = ENG_ALPHABETIC.indexOf(formulation[0].toLower());
            if(index < 0) {
                throw InvalidAnswerOption(src);
            }
        }
    }

    if(0 <= index && index < con.size()) {
        return index;
    } else {
        throw InvalidAnswerOption(src);
    }
}
