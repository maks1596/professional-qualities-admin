#include "ScaleStatisticsAssembler.h"

#include "../View/ScaleStatisticsForm.h"

ScaleStatisticsForm *ScaleStatisticsAssembler::assembly(const ScaleStatistics &scaleStatistics, QWidget *parent) {
    auto view = new ScaleStatisticsForm(parent);
    return view;
}
