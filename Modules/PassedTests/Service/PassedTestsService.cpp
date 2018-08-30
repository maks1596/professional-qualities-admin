#include "PassedTestsService.h"

#include <QJsonArray>
#include <QJsonValue>

#include "Entities/Statistics/PassedTest/PassedTest.h"
#include "Entities/Statistics/PassedTestPreview/PassedTestPreview.h"
#include "Requester/Requester.h"
#include "JsonArraySerialization.h"

//  :: Constants ::

const QString GET_PREVIEWS_API = "statistics";
const QString GET_PASSED_TEST_API = "statistics/%1";

//  :: Lifecycle ::

PassedTestsService::PassedTestsService(QObject *parent/*= nullptr*/)
    : BaseService(parent) { }

//  :: Public slots ::

void PassedTestsService::getPreviews() const {
    auto requester = makeRequesterWithDefaultErrorOutput();
    connect(requester, SIGNAL(success(QJsonArray)),
            SLOT(onPreviewsGot(QJsonArray)));
    requester->sendRequest(GET_PREVIEWS_API);
}

void PassedTestsService::getPassedTest(int id) const {
    auto requster = makeRequesterWithDefaultErrorOutput();
    connect(requster, SIGNAL(success(QJsonObject)),
            SLOT(onPassedTestGot(QJsonObject)));
    requster->sendRequest(GET_PASSED_TEST_API.arg(id));
}

//  :: Private slots ::

void PassedTestsService::onPreviewsGot(const QJsonArray &jsonPreviews) {
    auto previews = serializableObjectsFromJsonArray<QList, PassedTestPreview>(jsonPreviews);
    emit previewsGot(previews);
}

void PassedTestsService::onPassedTestGot(const QJsonObject &jsonPassedTest) {
    auto passedTest = makeWithJsonObject<PassedTest>(jsonPassedTest);
    emit passedTestGot(passedTest);
}
