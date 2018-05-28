#pragma once

#include <QJsonArray>

#include "Serializable/Object/SerializableObject.h"

/**
 * @brief Функция преобразует контейнер сериализуемых объектов в массив JSON
 * @param objects - контейнер сериализуемых объектов
 * @return массив JSON
 */
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

/**
 * @brief Функция преобразует массив JSON в контейнер сериализуемых объектов
 * @param jsonArray - массив JSON
 * @return контейнер сериализуемых объектов
 */
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

/**
 * @brief Функция преобразует контейнер произвольных значений в массив JSON
 * @param values - контейнер
 * @return массив JSON
 */
template<template <typename> typename List, typename T>
QJsonArray jsonArrayFromValues(const List<T> &values) {
    QJsonArray jsonArray;
    for (const auto &value : values) {
        // Передавать значение сначала в QVariant, а затем в QJsonValue обязательно
        // QJsonValue не может быть инициализирован, например, unsigned int
        auto variant = QVariant::fromValue(value);
        auto jsonValue = QJsonValue::fromVariant(variant);
        jsonArray += jsonValue;
    }
    return jsonArray;
}
