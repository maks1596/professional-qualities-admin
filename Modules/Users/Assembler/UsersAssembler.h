#pragma once

#include <tuple>

class QWidget;
class EntitiesOutput;

namespace UsersAssembler {
    std::tuple<QWidget *, EntitiesOutput *> assembly(QWidget *parent);
}
