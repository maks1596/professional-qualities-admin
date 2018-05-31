#include "ResultStatistics.h"

#include "NamedValue/NamedValue.h"
#include "JsonArraySerialization.h"
#include "Tree.h"

//  :: Constants ::

const QString FORMULATION_JSON_KEY = "formulation";
const QString TIMES_JSON_KEY = "times";
const QString FREQUENCY_JSON_KEY = "frequency";
const QString INDICATOR_GROUPS_JSON_KEY = "indicatorGroups";

const QString TIMES_NAME = "Количество";
const QString FREQUENCY_NAME = "Частота";

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

//  :: Public methods ::

Tree::NodePtr<NamedValue> ResultStatistics::toTreeNodePtr() const {
    NamedValue namedValue{getFormulation(), QVariant()};

    Tree::NodePtr<NamedValue> node(new Tree::Node<NamedValue>);
    node->data = namedValue;

    node->children.append(timesToNodePtr(node));
    node->children.append(frequencyToNodePtr(node));
    node->children.append(indicatorGroupsToNodePtrs(node));

    return node;
}

//  :: Private methods ::

Tree::NodePtr<NamedValue> ResultStatistics::timesToNodePtr(const Tree::NodePtr<NamedValue> &parent) const {
    NamedValue namedValue{TIMES_NAME, getTimes()};
    Tree::NodePtr<NamedValue> node(new Tree::Node<NamedValue>);
    node->data = namedValue;
    node->parent = parent;
    return node;
}

Tree::NodePtr<NamedValue> ResultStatistics::frequencyToNodePtr(const Tree::NodePtr<NamedValue> &parent) const {
    NamedValue namedValue{FREQUENCY_NAME, getFrequency()};
    Tree::NodePtr<NamedValue> node(new Tree::Node<NamedValue>);
    node->data = namedValue;
    node->parent = parent;
    return node;
}

Tree::NodePtrs<NamedValue> ResultStatistics::indicatorGroupsToNodePtrs(const Tree::NodePtr<NamedValue> &parent) const {
    Tree::NodePtrs<NamedValue> nodes;
    for (const auto &indicatorGroup : getIndicatorGroups()) {
        nodes.append(indicatorGroup.toTreeNodePtr(parent));
    }
    return nodes;
}
