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
