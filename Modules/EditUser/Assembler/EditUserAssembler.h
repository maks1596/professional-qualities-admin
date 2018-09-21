#pragma once

class QWidget;

class EditUserView;
class User;

namespace EditUserAssembler {
EditUserView *assembly(const User &user, QWidget *parent = nullptr);
}
