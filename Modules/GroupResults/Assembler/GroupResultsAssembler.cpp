#include "GroupResultsAssembler.h"

#include "../Model/GroupResultsColumnIndex.h"
#include "../Model/GroupResultsModel.h"

GroupResultsForm *GroupResultsAssembler::assembly(const GroupResults &groupResults,
                                                  QWidget *parent) {
    auto view = new GroupResultsForm(parent);
    auto model = new GroupResultsModel(groupResults, view);

    view->setModel(model);

    auto resizeLambda = [view](){view->resizeColumnToContents(NAME_COLUMN_INDEX);};
    QObject::connect(view, &QTreeView::collapsed, resizeLambda);
    QObject::connect(view, &QTreeView::expanded, resizeLambda);

    return view;
}
