#include "GroupsResultsAssembler.h"

#include "../Model/GroupsResultsColumnIndex.h"
#include "../Model/GroupsResultsModel.h"

GroupsResultsForm *GroupsResultsAssembler::assembly(const QList<GroupResults> &groupsResults,
                                                  QWidget *parent) {
    auto view = new GroupsResultsForm(parent);
    auto model = new GroupsResultsModel(groupsResults, view);

    view->setModel(model);
    view->setFrameShape(QFrame::NoFrame);

    auto resizeLambda = [view](){view->resizeColumnToContents(NAME_COLUMN_INDEX);};
    QObject::connect(view, &QTreeView::collapsed, resizeLambda);
    QObject::connect(view, &QTreeView::expanded, resizeLambda);
    resizeLambda();

    return view;
}
