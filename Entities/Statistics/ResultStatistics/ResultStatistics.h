#pragma once

#include "Serializable/Object/SerializableObject.h"

class ResultStatistics : public SerializableObject {
public:
    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

    //  :: Accessors ::

    QString getFormulation() const;
    void setFormulation(const QString &formulation);

    uint getTimes() const;
    void setTimes(const uint &times);

    double getFrequency() const;
    void setFrequency(double frequency);

    double getExpectedPoints() const;
    void setExpectedPoints(double expectedPoints);

    double getVariance() const;
    void setVariance(double variance);

private:
    QString m_formulation;
    uint m_times;
    double m_frequency;
    double m_expectedPoints;
    double m_variance;
};
