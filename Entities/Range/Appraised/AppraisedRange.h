#pragma once

#include <QScopedPointer>

#include "Entities/Range/Range.h"
#include "Serializable/Object/SerializableObject.h"

/**
 * @brief Класс представляет собой диапазон двух значений с определённой оценкой
 */
class AppraisedRange : SerializableObject {
public:
	//  :: Lifecycle ::
	//  :: Constructors ::
	AppraisedRange();
	AppraisedRange(const Range &range, const QString &result = "");
	AppraisedRange(const uint &lowerRangeValue,
				   const uint &upperRangeValue,
				   const QString &result = "");
	//  :: Copy ::
	AppraisedRange(const AppraisedRange &other);
	AppraisedRange &operator=(const AppraisedRange &other);

	//  :: Move ::
	AppraisedRange(AppraisedRange &&other);
	AppraisedRange &operator=(AppraisedRange &&other);

	//  :: Destructor ::
	virtual ~AppraisedRange() noexcept override;

	//  :: Accessors ::
	Range getRange() const;
	void setRange(const Range &range);

	uint getLowerRangeValue() const;
	void setLowerRangeValue(const uint &lowerRangeValue);

	uint getUpperRangeValue() const;
	void setUpperRangeValue(const uint &upperRangeValue);

	QString getResult() const;
	void setResult(const QString &result);

	//  :: Serializable ::
	virtual QJsonObject toJson() const override;
	virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
