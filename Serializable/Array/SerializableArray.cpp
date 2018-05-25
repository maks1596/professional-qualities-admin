#include "SerializableArray.h"

SerializableArray::operator QJsonArray() const {
	return toJson();
}

QVariantList SerializableArray::toVariantList() const {
	return toJson().toVariantList();
}
SerializableArray::operator QVariantList() const {
	return toVariantList();
}

void SerializableArray::initWithVariantList(const QVariantList &variantList) {
	return initWithJsonArray(QJsonArray::fromVariantList(variantList));
}
