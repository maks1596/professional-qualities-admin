#pragma once

class QWidget;
class PassedTest;
class PassedTestForm;

namespace PassedTestAssembler {
PassedTestForm *assembly(const PassedTest &passedTest,
                         QWidget *parent = nullptr);
}
