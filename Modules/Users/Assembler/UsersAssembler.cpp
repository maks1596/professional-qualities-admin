#include "UsersAssembler.h"

#include "../Controller/UsersController.h"
#include "../Model/UsersModel.h"
#include "../Service/UsersService.h"
#include "../View/UsersForm.h"

std::tuple<QWidget *, EntitiesOutput *> UsersAssembler::assembly(QWidget *parent) {
    auto view = new UsersForm(parent);
    auto model = new UsersModel(view);
    auto service = new UsersService(view);
    auto controller = new UsersController(view, model, service);

    view->setModel(model);

    return std::make_tuple(view, controller);
}
