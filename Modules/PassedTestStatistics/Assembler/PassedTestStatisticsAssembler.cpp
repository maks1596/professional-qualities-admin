#include "PassedTestStatisticsAssembler.h"

#include "../View/PassedTestStatisticsForm.h"

PassedTestStatisticsForm *PassedTestStatisticsAssembler::assembly(const PassedTest &/*passedTest*/, QWidget *parent) {
    auto view = new PassedTestStatisticsForm(parent);
    return view;
}
