#include "TestsController.h"

#include <QModelIndex>

#include "../View/TestsForm.h"
#include "../Service/TestsService.h"
#include "../Model/TestsModel.h"

#include "Entities/Test/Test.h"

//  :: Lifecycle ::

TestsController::TestsController(TestsForm *view,
                                 TestsModel *model,
                                 TestsService *service)
    : QObject(view),
      m_view(view),
      m_model(model),
      m_service(service)
{
    connectView();
    connectService();
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
}

void TestsController::connectService() {
    connect(m_service, &TestsService::testsGot,
            m_model, &TestsModel::setTests);
    connect(m_service, &TestsService::error,
            m_view, &TestsForm::showCriticalMessage);
    connect(m_service, &TestsService::testGot,
            m_view, &TestsForm::showEditTestView);
    connect(m_service, &TestsService::testIsUsed,
            m_view, &TestsForm::showTestIsUsedMessage);
}
