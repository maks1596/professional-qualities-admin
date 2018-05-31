#include "ResultStatistics.h"

#include "JsonArraySerialization.h"
#include "Tree.h"

//  :: Constants ::

const QString FORMULATION_JSON_KEY = "formulation";
const QString TIMES_JSON_KEY = "times";
const QString FREQUENCY_JSON_KEY = "frequency";
const QString INDICATOR_GROUPS_JSON_KEY = "indicatorGroups";

//  :: Serializable ::

QJsonObject ResultStatistics::toJson() const {
    QJsonObject json;

    json[FORMULATION_JSON_KEY] = getFormulation();
    json[TIMES_JSON_KEY] = static_cast<int>(getTimes());
    json[FREQUENCY_JSON_KEY] = getFrequency();
    json[INDICATOR_GROUPS_JSON_KEY] =
            jsonArrayFromSerializableObjects(getIndicatorGroups());

    return json;
}

void ResultStatistics::initWithJsonObject(const QJsonObject &json) {
    if (json.contains(FORMULATION_JSON_KEY) && json[FORMULATION_JSON_KEY].isString()) {
        setFormulation(json[FORMULATION_JSON_KEY].toString());
    }
    if (json.contains(TIMES_JSON_KEY) && json[TIMES_JSON_KEY].isDouble()) {
        setTimes(json[TIMES_JSON_KEY].toInt());
    }
    if (json.contains(FREQUENCY_JSON_KEY) && json[FREQUENCY_JSON_KEY].isDouble()) {
        setFrequency(json[FREQUENCY_JSON_KEY].toDouble());
    }
    if (json.contains(INDICATOR_GROUPS_JSON_KEY) &&
            json[INDICATOR_GROUPS_JSON_KEY].isArray()) {
        auto jsonArray = json[INDICATOR_GROUPS_JSON_KEY].toArray();
        setIndicatorGroups(serializableObjectsFromJsonArray<QList, IndicatorGroup>(jsonArray));
    }
}

//  :: Public accessors ::
//  :: Formulation ::
QString ResultStatistics::getFormulation() const {
    return m_formulation;
}
void ResultStatistics::setFormulation(const QString &formulation) {
    m_formulation = formulation;
}

//  :: Times ::
uint ResultStatistics::getTimes() const {
    return m_times;
}
void ResultStatistics::setTimes(const uint &times) {
    m_times = times;
}

//  :: Frequency ::
double ResultStatistics::getFrequency() const {
    return m_frequency;
}
void ResultStatistics::setFrequency(double frequency) {
    m_frequency = frequency;
}
//  :: Indicator groups ::
const QList<IndicatorGroup> &ResultStatistics::getIndicatorGroups() const {
    return m_indicatorGroups;
}
void ResultStatistics::setIndicatorGroups(const QList<IndicatorGroup> &indicatorGroups) {
    m_indicatorGroups = indicatorGroups;
}

Tree::NodePtr<Indicator> ResultStatistics::toTreeNodePtr() const {
    Tree::NodePtr<Indicator> node(new Tree::Node<Indicator>);
    node->data.setName(getFormulation());
    node->children = indicatorGroupsToNodePtrs(node);
    return node;
}

Tree::NodePtrs<Indicator> ResultStatistics::indicatorGroupsToNodePtrs(const Tree::NodePtr<Indicator> &parent) const {
    Tree::NodePtrs<Indicator> nodes;
    for (const auto &indicatorGroup : getIndicatorGroups()) {
        nodes.append(indicatorGroup.toTreeNodePtr(parent));
    }
    return nodes;
}
