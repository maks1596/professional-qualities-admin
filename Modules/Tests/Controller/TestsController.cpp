#include "TestsController.h"

#include <QModelIndex>

#include "../View/TestsForm.h"
#include "../Service/TestsService.h"
#include "../Model/TestsModel.h"

#include "Entities/Test/Test.h"

//  :: Constants ::

const int UPDATE_TIMING = 5000;

//  :: Lifecycle ::

TestsController::TestsController(TestsForm *view,
                                 TestsModel *model,
                                 TestsService *service)
    : EntitiesOutput(view),
      m_view(view),
      m_model(model),
      m_service(service)
{
    connectView();
    connectService();

    m_timer.setInterval(UPDATE_TIMING);
    connect(&m_timer, &QTimer::timeout,
            m_service, &TestsService::getTests);
    m_timer.start();

    m_service->getTests();
}

//  :: Private slots ::

void TestsController::onTestClicked(const QModelIndex &idx) {
    if (idx.isValid()) {
        if (idx.column() == m_model->getRemoveColumnIndex()) {
            m_view->showRemoveTestDialog(idx.row());
        }
    }
}

void TestsController::onTestDoubleClicked(const QModelIndex &idx) {
    if (idx.isValid()) {
        auto testIndex = idx.row();
        if (idx.column() == m_model->getRemoveColumnIndex()) {
            m_view->showRemoveTestDialog(testIndex);
        } else {
            m_service->getTest(m_model->getTestId(testIndex));
        }
    }
}

void TestsController::onRemoveTestClicked(uint index) {
    m_service->removeTest(m_model->getTestId(index));
}

//  :: Private methods ::

void TestsController::connectView() {
    connect(m_view, &TestsForm::entityClicked,
            this, &TestsController::onTestClicked);
    connect(m_view, &TestsForm::entityDoubleClicked,
            this, &TestsController::onTestDoubleClicked);

    connect(m_view, &TestsForm::addButtonClicked,
            m_view, &TestsForm::showAddTestView);
    connect(m_view, &TestsForm::removeTestClicked,
            this, &TestsController::onRemoveTestClicked);

    connect(m_view, &TestsForm::backButtonClicked,
            m_view, &TestsForm::pop);
    connect(m_view, &TestsForm::error,
            this, &TestsController::error);
}

void TestsController::connectService() {
    connect(m_service, &TestsService::testsGot,
            m_model, &TestsModel::setTests);
    connect(m_service, &TestsService::error,
            this, &TestsController::statusMessage);

    connect(m_service, &TestsService::testGot,
            m_view, &TestsForm::showEditTestView);
    connect(m_service, &TestsService::testIsUsed,
            m_view, &TestsForm::showTestIsUsedMessage);
}
