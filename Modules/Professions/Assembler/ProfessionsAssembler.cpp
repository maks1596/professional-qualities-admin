#include "ProfessionsAssembler.h"

#include "../Model/ProfessionsListModel.h"
#include "../Service/ProfessionsService.h"

ProfessionsListModel *ProfessionsAssembler::assembly(QObject *parent) {
    auto model = new ProfessionsListModel(parent);
    auto service = new ProfessionsService(model);

    model->setService(service);
    return model;
}

ProfessionsListModel *ProfessionsAssembler::assemblyAndStart(QObject *parent) {
    auto model = assembly(parent);
    model->startUpdating();
    return model;
}
