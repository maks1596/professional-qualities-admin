#pragma once

#include <tuple>

class QWidget;
class AddUserOutput;

namespace AddUserAssembler {
    std::tuple<QWidget *, AddUserOutput *> assembly(QWidget *parent = nullptr);
}
