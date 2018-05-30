#pragma once

class QWidget;

class ScaleStatistics;
class ScaleStatisticsForm;

namespace ScaleStatisticsAssembler {
ScaleStatisticsForm *assembly(const ScaleStatistics &scaleStatistics, QWidget *parent);
}
