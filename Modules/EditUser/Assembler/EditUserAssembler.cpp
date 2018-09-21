#include "EditUserAssembler.h"

#include "../Controller/EditUserController.h"
#include "../Service/EditUserService.h"
#include "../View/EditUserView.h"

#include "Modules/Professions/Assembler/ProfessionsAssembler.h"
#include "Modules/Professions/Model/ProfessionsListModel.h"

EditUserView *EditUserAssembler::assembly(const User &user, QWidget *parent) {
    auto view = new EditUserView(user, parent);
    auto controller = new EditUserController(view);
    auto service = new EditUserService(controller);

    view->setProfessionsModel(ProfessionsAssembler::assemblyAndStart(view));

    controller->setView(view);
    controller->setService(service);

    QObject::connect(service, &EditUserService::error,
                     view, &EditUserView::showErrorMessageBox);

    return view;
}
