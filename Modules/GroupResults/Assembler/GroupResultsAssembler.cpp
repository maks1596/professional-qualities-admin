#include "GroupResultsAssembler.h"

#include <QTreeView>

#include "../Model/GroupResultsModel.h"

QTreeView *GroupResultsAssembler::assembly(const GroupResults &groupResults,
                                           QWidget *parent) {
    auto view = new QTreeView(parent);
    auto model = new GroupResultsModel(groupResults, view);

    view->setModel(model);

    return view;
}
