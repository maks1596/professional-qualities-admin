#include "AddUserAssembler.h"

#include "../Controller/AddUserController.h"
#include "../Service/AddUserService.h"
#include "../View/AddUserView.h"

#include "Modules/Professions/Assembler/ProfessionsAssembler.h"
#include "Modules/Professions/Model/ProfessionsListModel.h"

AddUserView *AddUserAssembler::assembly(QWidget *parent) {
    auto view = new AddUserView(User(), parent);
    auto controller = new AddUserController(view);
    auto service = new AddUserService(controller);

    controller->setView(view);
    controller->setService(service);

    view->setProfessionsModel(ProfessionsAssembler::assemblyAndStart(view));

    return view;
}
