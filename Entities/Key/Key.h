#pragma once

#include <QScopedPointer>

#include "Indexes.h"
#include "Serializable/Array/SerializableArray.h"

class PartOfKey;
class GeneralAnswerOptionsKey;
class UniqueAnswerOptionsKey;

/**
 * @brief Абстрактный класс является представлением ключа для проверки теста
 */
class Key : SerializableArray {
public:
	//  :: Lifecycle ::
	//  :: Constructors ::
	Key();

	//  :: Copy ::
	Key(const Key &other);
	Key &operator=(const Key &other);

	//  :: Move ::
	Key(Key &&other);
	Key &operator=(Key &&other);

	//  :: Destructor ::
	virtual ~Key() noexcept override;

	//  :: Accessors ::

	// Методы возвращают ссылку на часть ключа,
	// соответствующую переданному индексу
	const PartOfKey &at(uint index) const;
	const PartOfKey &operator[](uint index) const;
	PartOfKey &operator[](uint index);

	/**
	 * @brief Метод возвращает количество ключей в составе ключа
	 * @return количество частей
	 */
	uint amountOfParts() const;

	/**
	 * @brief Метод добавляет переданную часть ключа к сохранённым
	 * @param partOfKey - новая часть ключа
	 */
	void addPartOfKey(const PartOfKey &partOfKey);

	/**
	 * @brief Метод удаляет часть ключа, соответствующую переданному индексу
	 * @param index - индекс части ключа
	 */
	void deletePartOfKey(uint index);

	//  :: Points ::

	/**
	 * @brief Метод устанавливает количество баллов для последней части ключа
	 * @param points - количество баллов
	 */
	void setPoints(const uint &points);
	/**
	 * @brief Метод возвращает количество баллов для последней части ключа
	 * @return количество баллов
	 */
	uint getPoints() const;

	//  :: Transformations ::

	GeneralAnswerOptionsKey *toGeneralAnswerOptionsKey();
	GeneralAnswerOptionsKey *toGAOK();

	UniqueAnswerOptionsKey *toUniqueAnswerOptionsKey();
	UniqueAnswerOptionsKey *toUAOK();

	//  :: Serializable ::
	QJsonArray toJson() const;
	void initWithJsonArray(const QJsonArray &json);

protected:
	//  :: Accessors ::
	QList<PartOfKey> &getPartsOfKey();
	const QList<PartOfKey> &getPartsOfKey() const;

	PartOfKey &getCurrentPartOfKey();
	const PartOfKey &getCurrentPartOfKey() const;


private:
	//  :: Accessors ::
	int getCurrentPartOfKeyIndex() const;
	void setCurrentPartOfKeyIndex(int index);

	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
