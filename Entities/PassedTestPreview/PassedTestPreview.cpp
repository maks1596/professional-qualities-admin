#include "PassedTestPreview.h"

//  :: Constants ::

const QString ID_JSON_KEY = "id";
const QString NAME_JSON_KEY = "name";
const QString NUMBER_OF_PASSES_JSON_KEY = "numberOfPasses";

//  :: Lifecycle ::

PassedTestPreview::PassedTestPreview(int id, const QString &name, uint numberOfPasses) {
    setId(id);
    setName(name);
    setNumberOfPasses(numberOfPasses);
}

//  :: Public accessors ::
//  :: ID ::
int PassedTestPreview::getId() const {
    return m_id;
}
void PassedTestPreview::setId(int id) {
    m_id = id;
}

//  :: Name ::
QString PassedTestPreview::getName() const {
    return m_name;
}
void PassedTestPreview::setName(const QString &name) {
    m_name = name;
}

//  :: Number of passes ::
uint PassedTestPreview::getNumberOfPasses() const {
    return m_numberOfPasses;
}
void PassedTestPreview::setNumberOfPasses(uint numberOfPasses) {
    m_numberOfPasses = numberOfPasses;
}

//  :: Serializable ::

QJsonObject PassedTestPreview::toJson() const {
    QJsonObject json;
    json[ID_JSON_KEY] = getId();
    json[NAME_JSON_KEY] = getName();
    json[NUMBER_OF_PASSES_JSON_KEY] = static_cast<int>(getNumberOfPasses());
    return json;
}

void PassedTestPreview::initWithJsonObject(const QJsonObject &json) {
    if (json.contains(ID_JSON_KEY) && json[ID_JSON_KEY].isDouble()) {
        setId(json[ID_JSON_KEY].toInt());
    }
    if (json.contains(NAME_JSON_KEY) && json[NAME_JSON_KEY].isString()) {
        setName(json[NAME_JSON_KEY].toString());
    }
    if (json.contains(NUMBER_OF_PASSES_JSON_KEY) &&
            json[NUMBER_OF_PASSES_JSON_KEY].isDouble()) {
        setNumberOfPasses(json[NUMBER_OF_PASSES_JSON_KEY].toInt());
    }
}
