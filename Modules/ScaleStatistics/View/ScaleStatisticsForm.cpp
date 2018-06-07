#include "ScaleStatisticsForm.h"
#include "ui_ScaleStatisticsForm.h"

#include "../Model/ScaleStatisticsModel.h"
#include "Modules/GroupsResults/Assembler/GroupsResultsAssembler.h"
#include "Modules/GroupsResults/View/GroupsResultsForm.h"
#include "Modules/Correlations/Assembler/CorrelationsAssembler.h"
#include "Modules/Correlations/View/CorrelationsForm.h"

//  :: Lifecycle ::

ScaleStatisticsForm::ScaleStatisticsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScaleStatisticsForm)
{
    ui->setupUi(this);
}

ScaleStatisticsForm::~ScaleStatisticsForm() {
    delete ui;
}

//  :: Public accessors ::

ScaleStatisticsModel *ScaleStatisticsForm::getModel() const {
    return m_model;
}
void ScaleStatisticsForm::setModel(ScaleStatisticsModel *model) {
    m_model = model;

    ui->scaleNameLabel->setText(model->getScaleName());
    updateResultsTab();
    updateCorrelationsTab();
    ui->statisticsTabWidget->setCurrentIndex(SCALE_STATISTICS_RESULTS_TAB_INDEX);
}

//  :: Private methods ::

inline
void ScaleStatisticsForm::updateResultsTab() {
    removeTab(SCALE_STATISTICS_RESULTS_TAB_INDEX);

    auto groupsResults = getModel()->getGroupsResults();
    auto groupsResultsView = GroupsResultsAssembler::assembly(groupsResults, this);

    auto tabLabel = getModel()->getTabLabel(SCALE_STATISTICS_RESULTS_TAB_INDEX);
    ui->statisticsTabWidget->insertTab(SCALE_STATISTICS_RESULTS_TAB_INDEX,
                                       groupsResultsView,
                                       tabLabel);
}

inline
void ScaleStatisticsForm::updateCorrelationsTab() {
    removeTab(SCALE_STATISTICS_CORRELATIONS_TAB_INDEX);

    auto testId = getModel()->getTestId();
    auto scaleId = getModel()->getScaleId();
    auto correlationsView = CorrelationsAssembler::assembly(testId, scaleId, this);

    auto tabLabel = getModel()->getTabLabel(SCALE_STATISTICS_CORRELATIONS_TAB_INDEX);
    ui->statisticsTabWidget->insertTab(SCALE_STATISTICS_CORRELATIONS_TAB_INDEX,
                                       correlationsView,
                                       tabLabel);
}

inline
void ScaleStatisticsForm::removeTab(int index) {
    auto oldResultsTabWidget = ui->statisticsTabWidget->widget(index);
    if (oldResultsTabWidget != nullptr) {
        oldResultsTabWidget->deleteLater();
    }
    if (index < ui->statisticsTabWidget->count()) {
        ui->statisticsTabWidget->removeTab(index);
    }
}
