#include "PassedTestModel.h"

//  :: Lyfecycle ::

PassedTestModel::PassedTestModel(const PassedTest &passedTest, QObject *parent)
    : QAbstractListModel(parent)
{
    setPassedTest(passedTest);
}

//  :: QAbstractListModel

int PassedTestModel::rowCount(const QModelIndex &) const {
    return getPassedTest().getScales().size();
}

QVariant PassedTestModel::data(const QModelIndex &index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole) {
        return QVariant(getPassedTest().getScales().at(index.row()).getName());
    }
    return QVariant();
}

//  :: Public accessors ::

const PassedTest &PassedTestModel::getPassedTest() const {
    return m_passedTest;
}
void PassedTestModel::setPassedTest(const PassedTest &passedTest) {
    m_passedTest = passedTest;
}

//  :: Public methods ::

int PassedTestModel::getTestId() const {
    return getPassedTest().getId();
}

QString PassedTestModel::getPassedTestName() const {
    return getPassedTest().getName();
}

uint PassedTestModel::getNumberOfPasses() const {
    return getPassedTest().getNumberOfPasses();
}

ScaleStatistics PassedTestModel::getScaleStatistics(const QModelIndex &index) const {
    if (index.isValid()) {
        auto scales = getPassedTest().getScales();
        if (index.row() < scales.size()) {
            return scales.at(index.row());
        }
    }
    return ScaleStatistics();
}
