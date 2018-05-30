#pragma once

class QWidget;
class QTreeView;

class GroupResults;

namespace GroupResultsAssembler {
QTreeView *assembly(const GroupResults &groupResults, QWidget *parent);
}
