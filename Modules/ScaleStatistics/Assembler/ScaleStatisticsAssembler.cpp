#include "ScaleStatisticsAssembler.h"

#include "../View/ScaleStatisticsForm.h"
#include "../Model/ScaleStatisticsModel.h"

ScaleStatisticsForm *ScaleStatisticsAssembler::assembly(const ScaleStatistics &scaleStatistics, QWidget *parent) {
    auto view = new ScaleStatisticsForm(parent);
    auto model = new ScaleStatisticsModel(scaleStatistics, view);

    view->setModel(model);

    return view;
}
