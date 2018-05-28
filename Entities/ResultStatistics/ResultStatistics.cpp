#include "ResultStatistics.h"

//  :: Constants ::

const QString FORMULATION_JSON_KEY = "formulation";
const QString TIMES_JSON_KEY = "times";
const QString FREQUENCY_JSON_KEY = "frequency";
const QString EXPECTED_POINTS_JSON_KEY = "expectedPoints";
const QString VARIANCE_JSON_KEY = "variance";

//  :: Serializable ::

QJsonObject ResultStatistics::toJson() const {
    QJsonObject json;

    json[FORMULATION_JSON_KEY] = getFormulation();
    json[TIMES_JSON_KEY] = static_cast<int>(getTimes());
    json[FREQUENCY_JSON_KEY] = getFrequency();
    json[EXPECTED_POINTS_JSON_KEY] = getExpectedPoints();
    json[VARIANCE_JSON_KEY] = getVariance();

    return json;
}

void ResultStatistics::initWithJsonObject(const QJsonObject &json) {
    if (json.contains(FORMULATION_JSON_KEY) && json[FORMULATION_JSON_KEY].isString()) {
        setFormulation(json[FORMULATION_JSON_KEY].toString());
    }
    if (json.contains(TIMES_JSON_KEY) && json[TIMES_JSON_KEY].isDouble()) {
        setTimes(json[TIMES_JSON_KEY].toInt());
    }
    if (json.contains(FREQUENCY_JSON_KEY) && json[FREQUENCY_JSON_KEY].isDouble()) {
        setFrequency(json[FREQUENCY_JSON_KEY].toDouble());
    }
    if (json.contains(EXPECTED_POINTS_JSON_KEY) && json[EXPECTED_POINTS_JSON_KEY].isDouble()) {
        setExpectedPoints(json[EXPECTED_POINTS_JSON_KEY].toDouble());
    }
    if (json.contains(VARIANCE_JSON_KEY) && json[VARIANCE_JSON_KEY].isDouble()) {
        setVariance(json[VARIANCE_JSON_KEY].toDouble());
    }
}

//  :: Public accessors ::
//  :: Formulation ::
QString ResultStatistics::getFormulation() const {
    return m_formulation;
}
void ResultStatistics::setFormulation(const QString &formulation) {
    m_formulation = formulation;
}

//  :: Times ::
uint ResultStatistics::getTimes() const {
    return m_times;
}
void ResultStatistics::setTimes(const uint &times) {
    m_times = times;
}

//  :: Frequency ::
double ResultStatistics::getFrequency() const {
    return m_frequency;
}
void ResultStatistics::setFrequency(double frequency) {
    m_frequency = frequency;
}

//  :: Expected points ::
double ResultStatistics::getExpectedPoints() const {
    return m_expectedPoints;
}
void ResultStatistics::setExpectedPoints(double expectedPoints) {
    m_expectedPoints = expectedPoints;
}

//  :: Variance ::
double ResultStatistics::getVariance() const {
    return m_variance;
}
void ResultStatistics::setVariance(double variance) {
    m_variance = variance;
}
