#include "AppraisedRange.h"

//  :: Constants ::

const QString LOWER_RANGE_VALUE_KEY = "lowerRangeValue";
const QString UPPER_RANGE_VALUE_KEY = "upperRangeValue";
const QString RESULT_KEY = "result";

//  :: Implementation ::

struct AppraisedRange::Implementation {
	Range range;
	QString result;
};

//  :: Lifecycle ::
//  :: Constructors ::
AppraisedRange::AppraisedRange() : pimpl(new Implementation()) {}

AppraisedRange::AppraisedRange(const Range &range,
							   const QString &result/*= ""*/)
	: AppraisedRange()
{
	pimpl->range = range;
	pimpl->result = result;
}

AppraisedRange::AppraisedRange(const uint &lowerRangeValue,
							   const uint &upperRangeValue,
							   const QString &result/*= ""*/)
	: AppraisedRange({lowerRangeValue, upperRangeValue}, result)
{ }

//  :: Copy ::
AppraisedRange::AppraisedRange(const AppraisedRange &other)
	: pimpl(new Implementation(*other.pimpl))
{ }
AppraisedRange &AppraisedRange::operator=(const AppraisedRange &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
AppraisedRange::AppraisedRange(AppraisedRange &&other)
	: pimpl(other.pimpl.take())
{ }
AppraisedRange &AppraisedRange::operator=(AppraisedRange &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
AppraisedRange::~AppraisedRange() {}

//  :: Accessors ::
//  :: Range ::
Range AppraisedRange::getRange() const {
	return pimpl->range;
}
void AppraisedRange::setRange(const Range &range) {
	pimpl->range = range;
}

//  :: Lower range value ::
uint AppraisedRange::getLowerRangeValue() const {
	return pimpl->range.first;
}
void AppraisedRange::setLowerRangeValue(const uint &lowerRangeValue) {
	pimpl->range.first = lowerRangeValue;
}

//  :: Upper range value ::
uint AppraisedRange::getUpperRangeValue() const {
	return pimpl->range.second;
}
void AppraisedRange::setUpperRangeValue(const uint &upperRangeValue) {
	pimpl->range.second = upperRangeValue;
}

//  :: Result ::
QString AppraisedRange::getResult() const {
	return pimpl->result;
}
void AppraisedRange::setResult(const QString &result) {
	pimpl->result = result;
}

//  :: Serializable ::

QJsonObject AppraisedRange::toJson() const {
	QJsonObject json;
	json[LOWER_RANGE_VALUE_KEY] = static_cast<int>(getLowerRangeValue());
	json[UPPER_RANGE_VALUE_KEY] = static_cast<int>(getUpperRangeValue());
	json[RESULT_KEY] = getResult();
	return json;
}
void AppraisedRange::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(LOWER_RANGE_VALUE_KEY) &&
			json[LOWER_RANGE_VALUE_KEY].isDouble()) {
		setLowerRangeValue(json[LOWER_RANGE_VALUE_KEY].toInt());
	}
	if (json.contains(UPPER_RANGE_VALUE_KEY) &&
			json[UPPER_RANGE_VALUE_KEY].isDouble()) {
		setUpperRangeValue(json[UPPER_RANGE_VALUE_KEY].toInt());
	}
	if (json.contains(RESULT_KEY) && json[RESULT_KEY].isString()) {
		setResult(json[RESULT_KEY].toString());
	}
}
