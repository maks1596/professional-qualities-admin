#include "CorrelationsAssembler.h"

#include "../View/CorrelationsForm.h"
#include "../Model/CorrelationsModel.h"
#include "../Service/CorrelationsService.h"

CorrelationsForm *CorrelationsAssembler::assembly(int testId, int scaleId, QWidget *parent) {
    auto view = new CorrelationsForm(parent);
    auto model = new CorrelationsModel(view);
    auto service = new CorrelationsService(model);

    view->setModel(model);

    QObject::connect(service, &CorrelationsService::defaultGroupsCorrelationsGot,
                     model, &CorrelationsModel::setGroupsCorrelations);
    QObject::connect(service, &CorrelationsService::error,
                     view, &CorrelationsForm::error);
    QObject::connect(model, &CorrelationsModel::dataChanged,
                     [view](){
        view->resizeColumnsToContents();
        view->resizeRowsToContents();
    });

    service->getDefaultGroupsCorrelations(testId, scaleId);

    return view;
}
