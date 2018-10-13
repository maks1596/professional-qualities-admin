#include "UsersAssembler.h"

#include "../Controller/UsersController.h"
#include "../Model/UsersModel.h"
#include "../Service/UsersService.h"
#include "../View/UsersForm.h"

QWidget *UsersAssembler::assembly(QWidget *parent) {
    auto view = new UsersForm(parent);
}
