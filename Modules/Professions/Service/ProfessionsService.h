#pragma once

#include "BaseService/BaseService.h"

class ProfessionsService : public BaseService {
    Q_OBJECT
public:
    ProfessionsService(QObject *parent = nullptr);

    void getProfessions() const;

signals:
    void professionsGot(const QStringList &professions) const;

private slots:
    void onProfessionsJsonGot(const QJsonArray &jsonProfessions) const;
};
