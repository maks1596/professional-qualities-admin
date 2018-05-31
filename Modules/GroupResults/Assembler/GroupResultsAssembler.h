#pragma once

#include "../View/GroupResultsForm.h"

class QWidget;
class GroupResults;

namespace GroupResultsAssembler {
GroupResultsForm *assembly(const GroupResults &groupResults, QWidget *parent);
}
