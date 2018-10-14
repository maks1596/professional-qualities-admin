#pragma once

#include <tuple>

class QWidget;
class EntitiesOutput;

namespace TestsAssembler {
    std::tuple<QWidget *, EntitiesOutput *> assembly(QWidget *parent);
}
