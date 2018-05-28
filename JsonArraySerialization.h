#pragma once

#include <QJsonArray>
#include <QJsonValue>

#include "Serializable/Object/SerializableObject.h"

template<template<typename> typename List, class T,
         typename = typename std::enable_if<
             std::is_base_of<SerializableObject, T>::value>
         ::type>
QJsonArray jsonArrayFromSerializableObjects(const List<T> &objects) {
    QJsonArray jsonArray;
    for (const auto &object : objects) {
        jsonArray += object.toJson();
    }
    return jsonArray;
}

template<template<typename> typename List, class T,
         typename = typename std::enable_if<
             std::is_base_of<SerializableObject, T>::value>
         ::type>
List<T> serializableObjectsFromJsonArray(const QJsonArray &jsonArray) {
    List<T> result;
    for (const auto &jsonValue : jsonArray) {
        if (jsonValue.isObject()) {
            result += makeWithJsonObject<T>(jsonValue.toObject());
        }
    }
    return result;
}

template<template <typename> typename List, typename T>
QJsonArray jsonArrayFromValues(const List<T> &values) {
    QJsonArray jsonArray;
    for (const auto &value : values) {
        jsonArray += QJsonValue(value);
    }
    return jsonArray;
}
