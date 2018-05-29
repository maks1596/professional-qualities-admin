#include "PassedTestsAssembler.h"

#include "../View/PassedTestsForm.h"
#include "../Model/PassedTestsModel.h"
#include "../Service/PassedTestsService.h"

PassedTestsForm *PassedTestsAssembler::assembly(QWidget *parent) {
    auto view = new PassedTestsForm(parent);
    auto model = new PassedTestsModel(view);
    auto service = new PassedTestsService(model);

    view->setModel(model);
    model->setService(service);

    QObject::connect(service, &PassedTestsService::error,
                     view, &PassedTestsForm::error);
    QObject::connect(view, SIGNAL(passedTestSelected(int)),
                     service, SLOT(getPassedTest(int)));
    QObject::connect(service, SIGNAL(passedTestGot(PassedTest)),
                     view, SIGNAL(passedTestSelected(PassedTest)));

    return view;
}
