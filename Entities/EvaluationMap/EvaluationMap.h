#pragma once

#include <QScopedPointer>

#include "Serializable/Array/SerializableArray.h"
#include "Entities/Range/Range.h"

class AppraisedRange;

class EvaluationMap : SerializableArray {
public:
	//  :: Lifecycle ::
	//  :: Constructors ::
	EvaluationMap();

	//  :: Copy ::
	EvaluationMap(const EvaluationMap &other);
	EvaluationMap &operator=(const EvaluationMap &other);

	//  :: Move ::
	EvaluationMap(EvaluationMap &&other);
	EvaluationMap &operator=(EvaluationMap &&other);

	//  :: Destructor ::
	virtual ~EvaluationMap() noexcept override;

	//  :: Accessors

	// Методы индексации
	const AppraisedRange &at(uint index) const;
	const AppraisedRange &operator[](uint index) const;
	AppraisedRange &operator[](uint index);

	/**
	 * @brief Метод возвращает размер оценочной карты
	 * @return размер оценочноый карты
	 */
	uint size() const;

	/**
	 * @brief Метод добавляет оценённый диапазон значений к уже сохранённым
	 * @param range - диапазон значений
	 * @param result - оценка диапазона
	 */
	void addAppraisedRange(const Range &range, const QString &result = "");

	/**
	 * @brief Метод добавляет оценённый диапазон значений к уже сохранённым
	 * @param appraisedRange - оценйнный диапазон
	 */
	void addAppraisedRange(const AppraisedRange &appraisedRange);

	/**
	 * @brief Метод устанавливает оценку к последнему диапазону значений
	 * @param result - оценка диапазона
	 */
	void setResultToLastRange(const QString &result);

	/**
	 * @brief Метод удаляет диапазон на указанной позиции
	 * @param index - позиция диапазона
	 */
	void removeAt(uint index);

	//  :: Serializable ::
	QJsonArray toJson() const;
	void initWithJsonArray(const QJsonArray &json);

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
