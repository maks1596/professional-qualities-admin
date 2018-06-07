#include "PassedTestForm.h"
#include "ui_PassedTestForm.h"

#include <QDebug>
#include <QFontMetrics>
#include <QResizeEvent>

#include "../Model/PassedTestModel.h"

//  :: Lifeycle ::

PassedTestForm::PassedTestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PassedTestForm)
{
    ui->setupUi(this);
    connect(ui->scalesListView, &QListView::doubleClicked,
            this, &PassedTestForm::onScaleDoubleClicked);
}

PassedTestForm::~PassedTestForm() {
    delete ui;
}

//  :: Public accessors ::

PassedTestModel *PassedTestForm::getModel() const {
    return m_model;
}
void PassedTestForm::setModel(PassedTestModel *model) {
    m_model = model;

    setPassedTestName(model->getPassedTestName());
    ui->numberOfPassesLabel->setText(QString::number(model->getNumberOfPasses()));
    ui->scalesListView->setModel(model);
}

//  :: Protected methods ::

void PassedTestForm::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    updatePassedTestName();
}

//  :: Private slots ::

void PassedTestForm::onScaleDoubleClicked(const QModelIndex &index) {
    auto scaleStatistics = getModel()->getScaleStatistics(index);
    if (scaleStatistics.getId() > 0) {
        auto testId = getModel()->getTestId();
        emit scaleSelected(testId, scaleStatistics);
    }
}

//  :: Private methods ::

void PassedTestForm::updatePassedTestName() {
    setPassedTestName(getModel()->getPassedTestName());
}

void PassedTestForm::setPassedTestName(const QString &name) {
    auto font = ui->testNameLabel->font();
    auto width = ui->testNameLabel->width();
    QFontMetrics fontMetrics(font);

    auto elidedName = fontMetrics.elidedText(name, Qt::ElideRight, width);
    ui->testNameLabel->setText(elidedName);
}
