#pragma once

#include "BaseModel/BaseModel.h"

class PassedTestPreview;

class PassedTestsModel : public BaseModel {
    Q_OBJECT

public:
    PassedTestsModel(QObject *parent = nullptr);

    void getPreviews();

signals:
    void previewsGot(const QList<PassedTestPreview> &previews);

private slots:
    void onPreviewsGot(const QJsonArray &jsonPreviews);
};
