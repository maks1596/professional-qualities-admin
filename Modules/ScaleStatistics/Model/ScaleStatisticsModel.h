#pragma once

#include <QObject>

#include "Entities/Statistics/ScaleStatistics/ScaleStatistics.h"

class ScaleStatisticsModel : public QObject {
    Q_OBJECT

public:
    ScaleStatisticsModel(const ScaleStatistics &scaleStatistics,
                         QObject *parent = nullptr);

    ScaleStatistics getScaleStatistics() const;
    void setScaleStatistics(const ScaleStatistics &scaleStatistics);

    QString getScaleName() const;
    uint getNumberOfGroups() const;
    QString getNameOfGroup(uint groupIndex) const;
    GroupResults getGroupResults(uint groupIndex) const;

private:
    ScaleStatistics m_scaleStatistics;
};
