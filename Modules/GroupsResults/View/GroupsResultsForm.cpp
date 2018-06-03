#include "GroupsResultsForm.h"
#include "ui_GroupsResultsForm.h"

#include "../Model/GroupsResultsModel.h"
#include "Modules/GroupResults/Assembler/GroupResultsAssembler.h"

//  :: Lifecycle ::

GroupsResultsForm::GroupsResultsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupsResultsForm)
{
    ui->setupUi(this);
    ui->groupsTabWidget->clear();
}

GroupsResultsForm::~GroupsResultsForm() {
    delete ui;
}

//  :: Public accessors ::

GroupsResultsModel *GroupsResultsForm::getModel() const {
    return m_model;
}
void GroupsResultsForm::setModel(GroupsResultsModel *model) {
    m_model = model;

    ui->groupsTabWidget->clear();
    uint numberOfGroups = model->getNumberOfGroups();

    for (uint groupIndex = 0; groupIndex < numberOfGroups; ++groupIndex) {
        auto groupName = model->getGroupName(groupIndex);
        auto groupResults = model->getGroupResults(groupIndex);
        auto groupView = GroupResultsAssembler::assembly(groupResults, this);
        ui->groupsTabWidget->addTab(groupView, groupName);
    }
}
