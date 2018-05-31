#include "GroupResultsAssembler.h"

#include "../Model/GroupResultsModel.h"

GroupResultsForm *GroupResultsAssembler::assembly(const GroupResults &groupResults,
                                                  QWidget *parent) {
    auto view = new GroupResultsForm(parent);
    auto model = new GroupResultsModel(groupResults, view);

    view->setModel(model);

    return view;
}
