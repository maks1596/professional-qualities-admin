#include "ScaleStatistics.h"

#include "JsonArraySerialization.h"

//  :: Constants ::

const QString ID_JSON_KEY = "id";
const QString NAME_JSON_KEY = "name";
const QString PROGRAMMERS_RESULTS_JSON_KEY = "programmersResults";
const QString NON_PROGRAMMERS_RESULTS_JSON_KEY = "nonProgrammersResults";

//  :: Serializable ::

QJsonObject ScaleStatistics::toJson() const {
    QJsonObject json;

    json[ID_JSON_KEY] = getId();
    json[NAME_JSON_KEY] = getName();
    json[PROGRAMMERS_RESULTS_JSON_KEY] =
            jsonArrayFromSerializableObjects(getProgrammersResults());
    json[NON_PROGRAMMERS_RESULTS_JSON_KEY] =
            jsonArrayFromSerializableObjects(getNonProgrammersResults());

    return json;
}

void ScaleStatistics::initWithJsonObject(const QJsonObject &json) {
    if (json.contains(ID_JSON_KEY) && json[ID_JSON_KEY].isDouble()) {
        setId(json[ID_JSON_KEY].toInt());
    }
    if (json.contains(NAME_JSON_KEY) && json[NAME_JSON_KEY].isString()) {
        setName(json[NAME_JSON_KEY].toString());
    }
    if (json.contains(PROGRAMMERS_RESULTS_JSON_KEY) &&
            json[PROGRAMMERS_RESULTS_JSON_KEY].isArray()) {
        auto jsonArray = json[PROGRAMMERS_RESULTS_JSON_KEY].toArray();
        setProgrammersResults(
                    serializableObjectsFromJsonArray<QList, ResultStatistics>(jsonArray)
                    );
    }
    if (json.contains(NON_PROGRAMMERS_RESULTS_JSON_KEY) &&
            json[NON_PROGRAMMERS_RESULTS_JSON_KEY].isArray()) {
        auto jsonArray = json[NON_PROGRAMMERS_RESULTS_JSON_KEY].toArray();
        setNonProgrammersResults(
                    serializableObjectsFromJsonArray<QList, ResultStatistics>(jsonArray)
                    );
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

//  :: Programmers results ::
QList<ResultStatistics> ScaleStatistics::getProgrammersResults() const {
    return m_programmersResults;
}
void ScaleStatistics::setProgrammersResults(
        const QList<ResultStatistics> &programmersResults
        ) {
    m_programmersResults = programmersResults;
}

//  :: Non programmers results ::
QList<ResultStatistics> ScaleStatistics::getNonProgrammersResults() const {
    return m_nonProgrammersResults;
}
void ScaleStatistics::setNonProgrammersResults(
        const QList<ResultStatistics> &nonProgrammersResults
        ) {
    m_nonProgrammersResults = nonProgrammersResults;
}
