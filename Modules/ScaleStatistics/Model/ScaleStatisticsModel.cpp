#include "ScaleStatisticsModel.h"

//  :: Constants ::

const QString RESULTS_TAB_LABEL = "Результаты";
const QString CORRELATIONS_TAB_LABEL = "Корреляции";

//  :: Lifecycle ::

ScaleStatisticsModel::ScaleStatisticsModel(int testId,
                                           const ScaleStatistics &scaleStatistics,
                                           QObject *parent)
    : QObject(parent)
{
    setTestId(testId);
    setScaleStatistics(scaleStatistics);
}

//  :: Public accessors ::
//  :: Test ID ::
void ScaleStatisticsModel::setTestId(int testId) {
    m_testId = testId;
}
int ScaleStatisticsModel::getTestId() const {
    return m_testId;
}

//  :: Scale statistics ::
const ScaleStatistics &ScaleStatisticsModel::getScaleStatistics() const {
    return m_scaleStatistics;
}
void ScaleStatisticsModel::setScaleStatistics(const ScaleStatistics &scaleStatistics) {
    m_scaleStatistics = scaleStatistics;
}

//  :: Public methods ::

int ScaleStatisticsModel::getScaleId() const {
    return getScaleStatistics().getId();
}

QString ScaleStatisticsModel::getScaleName() const {
    return getScaleStatistics().getName();
}

const QList<GroupResults> &ScaleStatisticsModel::getGroupsResults() const {
    return getScaleStatistics().getGroupsResults();
}

QString ScaleStatisticsModel::getTabLabel(ScaleStatisticsTabIndex index) const {
    switch (index) {
    case SCALE_STATISTICS_RESULTS_TAB_INDEX: {
        return RESULTS_TAB_LABEL;
    } break;

    case SCALE_STATISTICS_CORRELATIONS_TAB_INDEX: {
        return CORRELATIONS_TAB_LABEL;
    } break;

    default: {
        return QString();
    } break;
    }
}
