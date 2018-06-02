#pragma once

class QWidget;
class CorrelationsForm;

namespace CorrelationsAssembler {
CorrelationsForm *assembly(int testId, int scaleId, QWidget *parent);
}
