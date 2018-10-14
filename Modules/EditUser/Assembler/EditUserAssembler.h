#pragma once

#include <tuple>

class QWidget;

class EditUserOutput;
class User;

namespace EditUserAssembler {
std::tuple<QWidget *, EditUserOutput *> assembly(const User &user, QWidget *parent = nullptr);
}
