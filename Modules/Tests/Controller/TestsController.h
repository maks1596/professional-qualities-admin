#pragma once

#include "EntitesOutput/EntitiesOutput.h"

#include <QTimer>

class TestsForm;
class TestsModel;
class TestsService;

class TestsController : public EntitiesOutput {
    Q_OBJECT
public:
    TestsController(TestsForm *view,
                    TestsModel *model,
                    TestsService *service);

private slots:
    void onTestClicked(const QModelIndex &idx);
    void onTestDoubleClicked(const QModelIndex &idx);
    void onRemoveTestClicked(uint index);

private:
    void connectView();
    void connectService();

    TestsForm *m_view = nullptr;
    TestsModel *m_model = nullptr;
    TestsService *m_service = nullptr;
    QTimer m_timer;
};
