#include "PassedTestStatisticsAssembler.h"

#include "../View/PassedTestStatisticsForm.h"

PassedTestStatisticsForm *PassedTestStatisticsAssembler::assembly(int /*passedTestId*/, QWidget *parent) {
    auto view = new PassedTestStatisticsForm(parent);
    return view;
}
