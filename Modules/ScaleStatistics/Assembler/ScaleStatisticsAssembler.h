#pragma once

class QWidget;

class ScaleStatistics;
class ScaleStatisticsForm;

namespace ScaleStatisticsAssembler {
ScaleStatisticsForm *assembly(int testId,
                              const ScaleStatistics &scaleStatistics,
                              QWidget *parent = nullptr);
}
