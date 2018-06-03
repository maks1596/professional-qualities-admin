#include "GroupsResultsAssembler.h"

#include "../View/GroupsResultsForm.h"
#include "../Model/GroupsResultsModel.h"

GroupsResultsForm *GroupsResultsAssembler::assembly(const QList<GroupResults> &groupsResults,
                                                    QWidget *parent) {
    auto view = new GroupsResultsForm(parent);
    auto model = new GroupsResultsModel(groupsResults, view);

    view->setModel(model);
    return view;
}
