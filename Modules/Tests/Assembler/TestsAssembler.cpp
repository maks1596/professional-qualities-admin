#include "TestsAssembler.h"

#include "../Controller/TestsController.h"
#include "../Model/TestsModel.h"
#include "../Service/TestsService.h"
#include "../View/TestsForm.h"

std::tuple<QWidget *, EntitiesOutput *> TestsAssembler::assembly(QWidget *parent) {
    auto view = new TestsForm(parent);
    auto model = new TestsModel(view);
    auto service = new TestsService(view);
    auto controller = new TestsController(view, model, service);

    view->setModel(model);

    return std::make_tuple(view, controller);
}
