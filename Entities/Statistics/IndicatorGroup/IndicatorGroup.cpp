#include "IndicatorGroup.h"

#include "JsonArraySerialization.h"
#include "Tree.h"

//  :: Constants ::

const QString NAME_JSON_KEY = "name";
const QString INDICATORS_JSON_KEY = "indicators";

//  :: Serializable ::

QJsonObject IndicatorGroup::toJson() const {
    QJsonObject json;
    json[NAME_JSON_KEY] = getName();
    json[INDICATORS_JSON_KEY] = jsonArrayFromSerializableObjects(getIndicators());
    return json;
}

void IndicatorGroup::initWithJsonObject(const QJsonObject &json) {
    if (json.contains(NAME_JSON_KEY) && json[NAME_JSON_KEY].isString()) {
        setName(json[NAME_JSON_KEY].toString());
    }
    if (json.contains(INDICATORS_JSON_KEY) && json[INDICATORS_JSON_KEY].isArray()) {
        auto jsonArray = json[INDICATORS_JSON_KEY].toArray();
        setIndicators(serializableObjectsFromJsonArray<QList, Indicator>(jsonArray));
    }
}

//  :: Public accessors ::
//  :: Name ::
QString IndicatorGroup::getName() const {
    return m_name;
}
void IndicatorGroup::setName(const QString &name) {
    m_name = name;
}

//  :: Indicators ::
QList<Indicator> IndicatorGroup::getIndicators() const {
    return m_indicators;
}
void IndicatorGroup::setIndicators(const QList<Indicator> &indicators) {
    m_indicators = indicators;
}

//  :: Public methods ::

Tree::NodePtr<Indicator> IndicatorGroup::toTreeNodePtr(const Tree::NodePtr<Indicator> &parent) const {
    Tree::NodePtr<Indicator> node(new Tree::Node<Indicator>);
    node->data.setName(getName());
    node->parent = parent;
    node->children = indicatorsToTreeNodePtrs(node);
    return node;
}

Tree::NodePtrs<Indicator> IndicatorGroup::indicatorsToTreeNodePtrs(const Tree::NodePtr<Indicator> &parent) const {
    Tree::NodePtrs<Indicator> nodes;
    for (const auto &indicator : getIndicators()) {
        nodes.append(indicator.toTreeNodePtr(parent));
    }
    return nodes;
}
