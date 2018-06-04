#include "CorrelationValue.h"

//  :: Constants ::

const QString NAME_JSON_KEY = "name";
const QString FULL_NAME_JSON_KEY = "fullName";
const QString VALUE_JSON_KEY = "value";

//  :: Serializable ::

QJsonObject CorrelationValue::toJson() const {
    QJsonObject json;
    json[NAME_JSON_KEY] = getName();
    json[FULL_NAME_JSON_KEY] = getFullName();
    json[VALUE_JSON_KEY] = getValue().toString();
    return json;
}

void CorrelationValue::initWithJsonObject(const QJsonObject &json) {
    if (json.contains(NAME_JSON_KEY) && json[NAME_JSON_KEY].isString()) {
        setName(json[NAME_JSON_KEY].toString());
    }
    if (json.contains(FULL_NAME_JSON_KEY) &&
            json[FULL_NAME_JSON_KEY].isString()) {
        setFullName(json[FULL_NAME_JSON_KEY].toString());
    }
    if (json.contains(VALUE_JSON_KEY)) {
        setValue(json[VALUE_JSON_KEY].toVariant());
    }
}

//  :: Public accessors ::
//  :: Name ::
const QString &CorrelationValue::getName() const {
    return m_name;
}
void CorrelationValue::setName(const QString &name) {
    m_name = name;
}

//  :: Full name ::
QString CorrelationValue::getFullName() const {
    return m_fullName;
}
void CorrelationValue::setFullName(const QString &fullName) {
    m_fullName = fullName;
}

//  :: Value ::
const QVariant &CorrelationValue::getValue() const {
    return m_value;
}
void CorrelationValue::setValue(const QVariant &value) {
    m_value = value;
}


