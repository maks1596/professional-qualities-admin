#include "CorrelationsAssembler.h"

#include "../View/CorrelationsForm.h"
#include "../Model/CorrelationsModel.h"
#include "../Service/CorrelationsService.h"

CorrelationsForm *CorrelationsAssembler::assembly(int testId, int scaleId, QWidget *parent) {
    auto view = new CorrelationsForm(parent);
    auto model = new CorrelationsModel(testId, scaleId, view);
    auto service = new CorrelationsService(model);

    view->setModel(model);
    model->setService(service);

    QObject::connect(service, &CorrelationsService::error,
                     view, &CorrelationsForm::error);

    return view;
}
