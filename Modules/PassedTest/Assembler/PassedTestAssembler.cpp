#include "PassedTestAssembler.h"

#include "../View/PassedTestForm.h"
#include "../Model/PassedTestModel.h"

PassedTestForm *PassedTestAssembler::assembly(const PassedTest &passedTest, QWidget *parent) {
    auto view = new PassedTestForm(parent);
    auto model = new PassedTestModel(passedTest, view);

    view->setModel(model);

    return view;
}
