#pragma once

#include "BaseService/BaseService.h"

class PassedTestPreview;

class PassedTestsService : BaseService {
    Q_OBJECT

public:
    PassedTestsService(QObject *parent = nullptr);

    void getPreviews();

signals:
    void previewsGot(const QList<PassedTestPreview> &previews);

private slots:
    void onPreviewsGot(const QJsonArray &jsonPreviews);
};
