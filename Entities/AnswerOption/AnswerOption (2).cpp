#include "AnswerOption.h"

//  :: Constructors ::

AnswerOption::AnswerOption(const QString &formulation/*= ""*/) :
    m_formulation(formulation) {}

AnswerOption::AnswerOption(const int &id, const QString &formulation) :
    m_id(id),
    m_formulation(formulation) {}

//  :: Accessors ::

int AnswerOption::getID() const {
    return m_id;
}
void AnswerOption::setID(const int &id) {
    m_id = id;
}

QString AnswerOption::getFormulation() const {
    return m_formulation;
}
void AnswerOption::setFormulation(const QString &formulation) {
    m_formulation = formulation;
}

//  :: Public ::

bool AnswerOption::isEmpty() const {
    return m_formulation.isEmpty();
}

//  :: Serializable ::

QJsonObject AnswerOption::toJsonObject() const {
    QJsonObject result;
    result["id"] = m_id;
    result["formulation"] = m_formulation;
    return result;
}

void AnswerOption::initWithJsonObject(const QJsonObject &json) {
    if (json.contains("id") && json["id"].isDouble()) {
        m_id = json["id"].toInt();
    }
    if (json.contains("formulation") && json["formulation"].isString()) {
        m_formulation = json["formulation"].toString();
    }
}

//  :: Operators ::

bool operator==(const AnswerOption &lhs, const AnswerOption &rhs) {
    return lhs.getFormulation() == rhs.getFormulation();

}
