#include "SerializableObject.h"

SerializableObject::operator QJsonObject() const {
    return toJson();
}

QVariantMap SerializableObject::toVariantMap() const {
    return toJson().toVariantMap();
}
SerializableObject::operator QVariantMap() const {
    return toVariantMap();
}

void SerializableObject::initWithVariantMap(const QVariantMap &variantMap) {
    return initWithJsonObject(QJsonObject::fromVariantMap(variantMap));
}
