#include "PassedTestsModel.h"

#include <QJsonArray>
#include <QJsonValue>

#include "Entities/PassedTestPreview/PassedTestPreview.h"
#include "Requester/Requester.h"

//  :: Constants ::

const QString GET_PREVIEWS_API = "statistics";

//  :: Lifecycle ::

PassedTestsModel::PassedTestsModel(QObject *parent/*= nullptr*/)
    : BaseModel(parent) { }

//  :: Public methods ::

void PassedTestsModel::getPreviews() {
    auto requester = makeRequester();
    connect(requester, SIGNAL(success(QJsonArray)),
            SLOT(onPreviewsGot(QJsonArray)));
    requester->sendRequest(GET_PREVIEWS_API);
}

//  :: Private slots ::

void PassedTestsModel::onPreviewsGot(const QJsonArray &jsonPreviews) {
    QList<PassedTestPreview> previews;
    for (const auto &jsonValue : jsonPreviews) {
        if (jsonValue.isObject()) {
            auto jsonObject = jsonValue.toObject();
            PassedTestPreview preview;
            preview.initWithJsonObject(jsonObject);
            previews += preview;
        }
    }
    emit previewsGot(previews);
}
