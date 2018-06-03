#pragma once

template<typename>
class QList;
class QWidget;

class GroupResults;
class GroupsResultsForm;

namespace GroupsResultsAssembler {
GroupsResultsForm *assembly(const QList<GroupResults> &groupsResults,
                            QWidget *parent);
}
