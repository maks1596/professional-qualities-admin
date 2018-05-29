#pragma once

class QWidget;
class PassedTest;
class PassedTestStatisticsForm;

namespace PassedTestStatisticsAssembler {
PassedTestStatisticsForm *assembly(const PassedTest &passedTest, QWidget *parent);
}
