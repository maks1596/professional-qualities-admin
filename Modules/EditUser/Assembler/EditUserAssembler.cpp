#include "EditUserAssembler.h"

#include "../Controller/EditUserController.h"
#include "../Service/EditUserService.h"
#include "../View/EditUserView.h"

#include "Modules/Professions/Service/ProfessionsService.h"

EditUserView *EditUserAssembler::assembly(const User &user, QWidget *parent) {
    auto view = new EditUserView(user, parent);
    auto controller = new EditUserController(user, view);
    auto service = new EditUserService(controller);

    ProfessionsService::getProfessions(
                [view](const QStringList &professions)
                { view->setProfessions(professions); });

    controller->setView(view);
    controller->setService(service);

    QObject::connect(service, &EditUserService::error,
                     view, &EditUserView::showErrorMessageBox);

    return view;
}
