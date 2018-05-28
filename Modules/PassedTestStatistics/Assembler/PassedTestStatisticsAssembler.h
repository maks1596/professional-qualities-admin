#pragma once

class QWidget;
class PassedTestStatisticsForm;

namespace PassedTestStatisticsAssembler {
PassedTestStatisticsForm *assembly(int passedTestId, QWidget *parent);
}
