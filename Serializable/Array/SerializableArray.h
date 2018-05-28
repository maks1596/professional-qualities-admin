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

/**
 * @brief Вспомогательная функция для десериализации JSON-массива в объект типа Т.
 * Если тип Т не является наследникм SerializableArray, то
 * компилятор не сгенерирует для него функцию.
 * @param json - массив JSON
 * @return десериализованный из JSON-массива обект типа Т
 */
template<class T,
         typename = typename std::enable_if<
             std::is_base_of<SerializableArray, T>::value>
         ::type>
T makeWithJsonArray(const QJsonArray &json) {\
    T object;
    object.initWithJsonArray(json);
    return object;
}

/**
 * @brief Вспомогательная функция для десериализации QVariantList в объект типа Т.
 * @param variantList - вариативный список
 * @return десериализованный из QVariantList объект типа Т
 */
template<class T>
T makeWithVariantList(const QVariantList &list) {
    return makeWithJsonArray<T>(QJsonArray::fromVariantList(list));
}
