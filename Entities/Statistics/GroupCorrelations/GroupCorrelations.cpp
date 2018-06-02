#include "GroupCorrelations.h"

#include "JsonArraySerialization.h"

//  :: Constants ::

const QString GROUP_NAME_JSON_KEY = "groupName";
const QString CORRELATION_VALUES_JSON_KEY = "correlationValues";

//  :: Serializable ::

QJsonObject GroupCorrelations::toJson() const {
    QJsonObject json;
    json[GROUP_NAME_JSON_KEY] = getGroupName();
    json[CORRELATION_VALUES_JSON_KEY] =
            jsonArrayFromSerializableObjects(getCorrelationValues());
    return json;
}

void GroupCorrelations::initWithJsonObject(const QJsonObject &json) {
    if (json.contains(GROUP_NAME_JSON_KEY) && json[GROUP_NAME_JSON_KEY].isString()) {
        setGroupName(json[GROUP_NAME_JSON_KEY].toString());
    }
    if (json.contains(CORRELATION_VALUES_JSON_KEY) &&
            json[CORRELATION_VALUES_JSON_KEY].isArray()) {
        auto jsonArray = json[CORRELATION_VALUES_JSON_KEY].toArray();
        setCorrelationValues(serializableObjectsFromJsonArray<QList, CorrelationValue>(jsonArray));
    }
}

//  :: Public accessors ::
//  :: Group name ::
const QString &GroupCorrelations::getGroupName() const {
    return m_groupName;
}
void GroupCorrelations::setGroupName(const QString &groupName) {
    m_groupName = groupName;
}

//  :: Correlation values ::
const QList<CorrelationValue> &GroupCorrelations::getCorrelationValues() const {
    return m_correlationValues;
}
void GroupCorrelations::setCorrelationValues(const QList<CorrelationValue> &correlationValues) {
    m_correlationValues = correlationValues;
}
