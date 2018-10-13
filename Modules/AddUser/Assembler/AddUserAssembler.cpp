#include "AddUserAssembler.h"

#include "../Controller/AddUserController.h"
#include "../Service/AddUserService.h"
#include "../View/AddUserView.h"

#include "Modules/Professions/Service/ProfessionsService.h"

AddUserView *AddUserAssembler::assembly(QWidget *parent) {
    auto view = new AddUserView(parent);
    auto controller = new AddUserController(view);
    auto service = new AddUserService(controller);

    controller->setView(view);
    controller->setService(service);

    ProfessionsService::getProfessions(
                [view](const QStringList &professions)
                { view->setProfessions(professions); });


    return view;
}
