#pragma once

#include "BaseService/BaseService.h"

class GroupCorrelations;

class CorrelationsService : public BaseService {
public:
    explicit CorrelationsService(QObject *parent = nullptr);

public slots:
    void getDefaultGroupsCorrelations(int testId, int scaleId) const;

signals:
    void defaultGroupsCorrelationsGot(const QList<GroupCorrelations> &groupsCorrelations);

private slots:
    void defaultGroupsCorrelationsJsonGot(const QJsonArray &groupsCorrelationsJson);
};
