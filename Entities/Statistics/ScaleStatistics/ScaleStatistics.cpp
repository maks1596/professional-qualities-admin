#include "ScaleStatistics.h"

#include "JsonArraySerialization.h"

//  :: Constants ::

const QString ID_JSON_KEY = "id";
const QString NAME_JSON_KEY = "name";
const QString GROUPS_RESULTS_JSON_KEY = "groupsResults";

//  :: Serializable ::

QJsonObject ScaleStatistics::toJson() const {
    QJsonObject json;

    json[ID_JSON_KEY] = getId();
    json[NAME_JSON_KEY] = getName();
    json[GROUPS_RESULTS_JSON_KEY] =
            jsonArrayFromSerializableObjects(getGroupsResults());

    return json;
}

void ScaleStatistics::initWithJsonObject(const QJsonObject &json) {
    if (json.contains(ID_JSON_KEY) && json[ID_JSON_KEY].isDouble()) {
        setId(json[ID_JSON_KEY].toInt());
    }
    if (json.contains(NAME_JSON_KEY) && json[NAME_JSON_KEY].isString()) {
        setName(json[NAME_JSON_KEY].toString());
    }
    if (json.contains(GROUPS_RESULTS_JSON_KEY) &&
            json[GROUPS_RESULTS_JSON_KEY].isArray()) {
        auto jsonArray = json[GROUPS_RESULTS_JSON_KEY].toArray();
        setGroupsResults(serializableObjectsFromJsonArray<QList, GroupResults>(jsonArray));
    }
}

//  :: Public accessors ::
//  :: ID ::
int ScaleStatistics::getId() const {
    return m_id;
}
void ScaleStatistics::setId(int id) {
    m_id = id;
}

//  :: Name ::
QString ScaleStatistics::getName() const {
    return m_name;
}
void ScaleStatistics::setName(const QString &name) {
    m_name = name;
}

//  :: Groups results ::
const QList<GroupResults> &ScaleStatistics::getGroupsResults() const {
    return m_groupsResults;
}
void ScaleStatistics::setGroupsResults(const QList<GroupResults> &groupsResults) {
    m_groupsResults = groupsResults;
}
