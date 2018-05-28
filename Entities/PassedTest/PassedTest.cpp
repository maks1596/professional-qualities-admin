#include "PassedTest.h"

#include "JsonArraySerialization.h"

//  :: Constants ::

const QString SCALES_JSON_KEY = "scales";

//  :: Lifecycle ::

PassedTest::PassedTest(int id) : PassedTestPreview() {
    setId(id);
}

//  :: Serializable ::

QJsonObject PassedTest::toJson() const {
    auto json = PassedTestPreview::toJson();
    json[SCALES_JSON_KEY] = jsonArrayFromSerializableObjects(getScales());
    return json;
}

void PassedTest::initWithJsonObject(const QJsonObject &json) {
    PassedTestPreview::initWithJsonObject(json);

}

//  :: Public accessors ::
//  :: Scales ::
QList<ScaleStatistics> PassedTest::getScales() const {
    return m_scales;
}
void PassedTest::setScales(const QList<ScaleStatistics> &scales) {
    m_scales = scales;
}
