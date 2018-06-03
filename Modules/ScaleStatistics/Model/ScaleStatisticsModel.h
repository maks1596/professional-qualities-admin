#pragma once

#include <QObject>

#include "Entities/Statistics/ScaleStatistics/ScaleStatistics.h"
#include "ScaleStatisticsTabIndex.h"

class ScaleStatisticsModel : public QObject {
    Q_OBJECT

public:

    //  :: Lifecycle ::

    ScaleStatisticsModel(int testId,
                         const ScaleStatistics &scaleStatistics,
                         QObject *parent = nullptr);

    //  :: Accessors ::

    int getTestId() const;
    void setTestId(int testId);

    const ScaleStatistics &getScaleStatistics() const;
    void setScaleStatistics(const ScaleStatistics &scaleStatistics);

    //  :: Methods ::

    int getScaleId() const;
    QString getScaleName() const;
    const QList<GroupResults> &getGroupsResults() const;

    QString getTabLabel(ScaleStatisticsTabIndex index) const;

private:
    int m_testId;
    ScaleStatistics m_scaleStatistics;
};
