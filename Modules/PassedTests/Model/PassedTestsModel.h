#pragma once

#include "BaseService/BaseService.h"

class PassedTestPreview;

class PassedTestsModel : public BaseService {
    Q_OBJECT

public:
    PassedTestsModel(QObject *parent = nullptr);

    void getPreviews();

signals:
    void previewsGot(const QList<PassedTestPreview> &previews);

private slots:
    void onPreviewsGot(const QJsonArray &jsonPreviews);
};
