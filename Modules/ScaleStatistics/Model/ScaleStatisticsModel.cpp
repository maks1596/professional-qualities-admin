#include "ScaleStatisticsModel.h"

//  :: Lifecycle ::

ScaleStatisticsModel::ScaleStatisticsModel(const ScaleStatistics &scaleStatistics,
                                           QObject *parent)
    : QObject(parent)
{
    setScaleStatistics(scaleStatistics);
}

//  :: Public accessors ::

ScaleStatistics ScaleStatisticsModel::getScaleStatistics() const {
    return m_scaleStatistics;
}
void ScaleStatisticsModel::setScaleStatistics(const ScaleStatistics &scaleStatistics) {
    m_scaleStatistics = scaleStatistics;
}

//  :: Public methods ::

QString ScaleStatisticsModel::getScaleName() const {
    return getScaleStatistics().getName();
}

uint ScaleStatisticsModel::getNumberOfGroups() const {
    return getScaleStatistics().getGroupsResults().size();
}

QString ScaleStatisticsModel::getNameOfGroup(uint groupIndex) const {
    if (groupIndex < getNumberOfGroups()) {
        return getScaleStatistics().getGroupsResults().at(groupIndex).getGroupName();
    }
    return QString();
}
