#include "PassedTestAssembler.h"

#include "../View/PassedTestForm.h"

PassedTestForm *PassedTestAssembler::assembly(const PassedTest &passedTest, QWidget *parent) {
    auto view = new PassedTestForm(parent);
    return view;
}
