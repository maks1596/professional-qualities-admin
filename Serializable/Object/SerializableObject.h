#pragma once

#include <QJsonObject>
#include <QVariantMap>

/**
 * @brief Абстрактный класс, объект которого можно преобразовать в объект JSON
 */
class SerializableObject {
public:
	virtual ~SerializableObject() noexcept = default;

    /**
     * @brief Абстрактный метод преобразует объект в JSON
     * @return объект класса в формате JSON
     */
	virtual QJsonObject toJson() const = 0;
    operator QJsonObject() const;

    /**
	 * @brief Метод преобразует объект в аналог JSON - VariantMap
     * @return объект класса, упакованный в словарь
     */
    QVariantMap toVariantMap() const;
    operator QVariantMap() const;

    /**
     * @brief Абстрактный метод инициализирует объект класса объектом JSON
     * @param json - объект JSON
     */
    virtual void initWithJsonObject(const QJsonObject &json) = 0;

    /**
     * @brief Метод инициализирует объект класса словаря
     * @param variantMap - словарь
     */
    void initWithVariantMap(const QVariantMap &variantMap);
};

/**
 * @brief Вспомогательная функция для десериализации JSON в объект типа Т.
 * Если тип Т не является наследникм SerializableObject, то
 * компилятор не сгенерирует для него функцию.
 * @param json - объект JSON
 * @return десериализованный из JSON обект типа Т
 */
template<class T,
         typename = typename std::enable_if<
             std::is_base_of<SerializableObject, T>::value>
         ::type>
T makeWithJsonObject(const QJsonObject &json) {\
    T object;
    object.initWithJsonObject(json);
    return object;
}

/**
 * @brief Вспомогательная функция для десериализации QVariantMap в объект типа Т.
 * @param map - объект QVariantMap
 * @return десериализованный из QVariantMap объект типа Т
 */
template<class T>
T makeWithVariantMap(const QVariantMap &map) {
    return makeWithJsonObject<T>(QJsonObject::fromVariantMap(map));
}

