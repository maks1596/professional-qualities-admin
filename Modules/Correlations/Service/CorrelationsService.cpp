#include "CorrelationsService.h"

#include "Entities/Statistics/GroupCorrelations/GroupCorrelations.h"
#include "JsonArraySerialization.h"
#include "Requester/Requester.h"

//  :: Constants ::

const QString CORRElATIONS_API = "statistics/correlations/%1/%2";

//  :: Lifecycle ::

CorrelationsService::CorrelationsService(QObject *parent)
    : BaseService(parent)
{ }

//  :: Public slots ::

void CorrelationsService::getDefaultGroupsCorrelations(int testId, int scaleId) const {
    auto requster = makeRequesterWithDefaultErrorOutput();
    connect(requster, SIGNAL(success(QJsonArray)),
            SLOT(defaultGroupsCorrelationsJsonGot(QJsonArray)));
    requster->sendRequest(CORRElATIONS_API.arg(testId).arg(scaleId));
}

//  :: Private slots ::

void CorrelationsService::defaultGroupsCorrelationsJsonGot(const QJsonArray &groupsCorrelationsJson) {
    auto groupsCorrelations = serializableObjectsFromJsonArray<QList, GroupCorrelations>(groupsCorrelationsJson);
    emit defaultGroupsCorrelationsGot(groupsCorrelations);
}
