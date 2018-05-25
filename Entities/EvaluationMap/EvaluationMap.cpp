#include "EvaluationMap.h"

#include "Entities/Range/Appraised/AppraisedRange.h"

struct EvaluationMap::Implementation {
	QList<AppraisedRange> appraisedRanges;
};

//  :: Lifecycle ::
//  :: Constructors ::
EvaluationMap::EvaluationMap() : pimpl(new Implementation()) {}

//  :: Copy ::
EvaluationMap::EvaluationMap(const EvaluationMap &other)
	: pimpl(new Implementation(*other.pimpl))
{ }
EvaluationMap &EvaluationMap::operator=(const EvaluationMap &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
EvaluationMap::EvaluationMap(EvaluationMap &&other) : pimpl(other.pimpl.take()) {}
EvaluationMap &EvaluationMap::operator=(EvaluationMap &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
EvaluationMap::~EvaluationMap() {}

//  :: Accessors ::

void EvaluationMap::addAppraisedRange(const AppraisedRange &appraisedRange) {
	pimpl->appraisedRanges.append(appraisedRange);
}

void EvaluationMap::addAppraisedRange(const Range &range,
									  const QString &result/*= ""*/) {
	addAppraisedRange({range, result});
}

void EvaluationMap::setResultToLastRange(const QString &result) {
	pimpl->appraisedRanges.last().setResult(result);
}

uint EvaluationMap::size() const {
	return pimpl->appraisedRanges.size();
}

void EvaluationMap::removeAt(uint index) {
	pimpl->appraisedRanges.removeAt(index);
}

//  :: Методы индексации ::
const AppraisedRange &EvaluationMap::at(uint index) const {
	return pimpl->appraisedRanges.at(index);
}
const AppraisedRange &EvaluationMap::operator[](uint index) const {
	return pimpl->appraisedRanges[index];
}
AppraisedRange &EvaluationMap::operator[](uint index) {
	return pimpl->appraisedRanges[index];
}

//  :: Serializable ::

QJsonArray EvaluationMap::toJson() const {
	QJsonArray json;
	for (const auto &appraisedRange : pimpl->appraisedRanges) {
		json.append(appraisedRange.toJson());
	}
	return json;
}

void EvaluationMap::initWithJsonArray(const QJsonArray &json) {
	pimpl->appraisedRanges.clear();
	for (const auto &jsonApprasedRange : json) {
		if (jsonApprasedRange.isObject()) {
			QJsonObject jsonObject = jsonApprasedRange.toObject();
			AppraisedRange appraisedRange;
			appraisedRange.initWithJsonObject(jsonObject);
			pimpl->appraisedRanges.append(appraisedRange);
		}
	}
}
