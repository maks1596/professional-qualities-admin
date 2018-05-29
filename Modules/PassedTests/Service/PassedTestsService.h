#pragma once

#include "BaseService/BaseService.h"

class PassedTest;
class PassedTestPreview;

class PassedTestsService : public BaseService {
    Q_OBJECT

public:
    PassedTestsService(QObject *parent = nullptr);

public slots:
    void getPreviews() const;
    void getPassedTest(int id) const;

signals:
    void previewsGot(const QList<PassedTestPreview> &previews);
    void passedTestGot(const PassedTest &passedTest);

private slots:
    void onPreviewsGot(const QJsonArray &jsonPreviews);
    void onPassedTestGot(const QJsonObject &jsonPassedTest);
};
