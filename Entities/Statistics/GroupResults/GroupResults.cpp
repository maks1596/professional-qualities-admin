#include "GroupResults.h"

#include "JsonArraySerialization.h"
#include "Tree.h"

//  :: Constants ::

const QString GROUP_NAME_JSON_KEY = "groupName";
const QString VALUE_JSON_KEY = "results";

//  :: Serilizable ::

QJsonObject GroupResults::toJson() const {
    QJsonObject json;
    json[GROUP_NAME_JSON_KEY] = getGroupName();
    json[VALUE_JSON_KEY] = jsonArrayFromSerializableObjects(getResults());
    return json;
}

void GroupResults::initWithJsonObject(const QJsonObject &json) {
    if (json.contains(GROUP_NAME_JSON_KEY) && json[GROUP_NAME_JSON_KEY].isString()) {
        setGroupName(json[GROUP_NAME_JSON_KEY].toString());
    }
    if (json.contains(VALUE_JSON_KEY) && json[VALUE_JSON_KEY].isArray()) {
        auto jsonArray = json[VALUE_JSON_KEY].toArray();
        setResults(serializableObjectsFromJsonArray<QList, ResultStatistics>(jsonArray));
    }
}

//  :: Public accessors ::
//  :: Group name ::
QString GroupResults::getGroupName() const {
    return m_groupName;
}
void GroupResults::setGroupName(const QString &groupName) {
    m_groupName = groupName;
}

//  :: Results ::
QList<ResultStatistics> GroupResults::getResults() const {
    return m_results;
}
void GroupResults::setResults(const QList<ResultStatistics> &results) {
    m_results = results;
}

Tree::Nodes<Indicator> GroupResults::resultsToTreeNodes() const {
    Tree::Nodes<Indicator> nodes;

    for (const auto &result : getResults()) {
        nodes.append(result.toTreeNode());
    }

    return nodes;
}
