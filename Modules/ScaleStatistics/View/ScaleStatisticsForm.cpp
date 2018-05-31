#include "ScaleStatisticsForm.h"
#include "ui_ScaleStatisticsForm.h"

#include "../Model/ScaleStatisticsModel.h"
#include "Modules/GroupResults/Assembler/GroupResultsAssembler.h"

//  :: Lifecycle ::

ScaleStatisticsForm::ScaleStatisticsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScaleStatisticsForm)
{
    ui->setupUi(this);

    connect(ui->backButton, &QPushButton::clicked,
            this, &ScaleStatisticsForm::backButtonClicked);
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
    updateGroupsResultsTabs();
}

//  :: Private methods ::

inline
void ScaleStatisticsForm::updateGroupsResultsTabs() {
    ui->groupsTabWidget->clear();
    uint numberOfGroups = getModel()->getNumberOfGroups();

    for (uint groupIndex = 0; groupIndex < numberOfGroups; ++groupIndex) {
        auto groupName = getModel()->getNameOfGroup(groupIndex);
        auto groupResults = getModel()->getGroupResults(groupIndex);
        auto groupView = GroupResultsAssembler::assembly(groupResults, this);
        ui->groupsTabWidget->addTab(groupView, groupName);
    }
}
