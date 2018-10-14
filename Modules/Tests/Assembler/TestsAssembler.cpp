#include "TestsAssembler.h"

#include "../Controller/TestsController.h"
#include "../Model/TestsModel.h"
#include "../Service/TestsService.h"
#include "../View/TestsForm.h"

QWidget *TestsAssembler::assembly(QWidget *parent) {
    auto view = new TestsForm(parent);
}
