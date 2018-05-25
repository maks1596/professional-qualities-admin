#pragma once

#include <QJsonArray>
#include <QVariantList>

/**
 * @brief Абстрактный класс, объект которого можно преобразовать в объект массив JSON
 */
class SerializableArray {
public:
	virtual ~SerializableArray() noexcept = default;

	/**
	 * @brief Абстрактный метод преобразует объект в JSON
	 * @return массив в формате JSON
	 */
	virtual QJsonArray toJson() const = 0;
	operator QJsonArray() const;

	/**
	 * @brief Метод преобразует объект в VariantList
	 * @return объект класса, упакованный в список
	 */
	QVariantList toVariantList() const;
	operator QVariantList() const;

	/**
	 * @brief Абстрактный метод инициализирует объект класса массвиом JSON
	 * @param json - массив JSON
	 */
	virtual void initWithJsonArray(const QJsonArray &json) = 0;

	/**
	 * @brief Метод инициализирует объект класса вариативным списком
	 * @param variantList - вариативный список
	 */
	void initWithVariantList(const QVariantList &variantList);
};
