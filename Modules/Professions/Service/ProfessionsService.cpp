#include "ProfessionsService.h"

#include <QJsonArray>

#include "Requester/Requester.h"

//  :: Constants ::

const QString GET_PROFESSIONS_API = "users/professions";

//  :: Lifecycle ::

ProfessionsService::ProfessionsService(QObject *parent)
    : BaseService(parent) { }

//  :: Public methods ::

void ProfessionsService::getProfessions() const {
    auto requester = makeRequesterWithDefaultErrorOutput();
    connect(requester, SIGNAL(success(QJsonArray)),
            SLOT(onProfessionsJsonGot(QJsonArray)));
    requester->sendRequest(GET_PROFESSIONS_API);
}

void ProfessionsService::getProfessions(const std::function<void (const QStringList &)> &receiver) {
    auto service = new ProfessionsService();

    connect(service, &ProfessionsService::professionsGot, receiver);
    connect(service, &ProfessionsService::error,
            [receiver](){ receiver(QStringList()); });

    connect(service, &ProfessionsService::professionsGot,
            service, &ProfessionsService::deleteLater);
    connect(service, &ProfessionsService::error,
            service, &ProfessionsService::deleteLater);

    service->getProfessions();
}

//  :: Private slots ::

void ProfessionsService::onProfessionsJsonGot(const QJsonArray &jsonProfessions) const {
    QStringList professions;
    for (const auto &jsonValue : jsonProfessions) {
        if (jsonValue.isString()) {
            professions.append(jsonValue.toString());
        }
    }
    emit professionsGot(professions);
}
