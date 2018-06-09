#pragma once

#include "../View/GroupsResultsForm.h"

template<typename>
class QList;
class QWidget;

class GroupResults;

namespace GroupsResultsAssembler {
GroupsResultsForm *assembly(const QList<GroupResults> &groupsResults, QWidget *parent);
}
