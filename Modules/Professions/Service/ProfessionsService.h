#pragma once

#include "BaseService/BaseService.h"

#include <functional>

class ProfessionsService : public BaseService {
    Q_OBJECT
public:
    ProfessionsService(QObject *parent = nullptr);

    void getProfessions() const;

    static void getProfessions(const std::function<void (const QStringList &)> &receiver);
signals:
    void professionsGot(const QStringList &professions) const;

private slots:
    void onProfessionsJsonGot(const QJsonArray &jsonProfessions) const;
};
