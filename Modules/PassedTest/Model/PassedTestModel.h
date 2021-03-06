#pragma once

#include <QAbstractListModel>

#include "Entities/Statistics/PassedTest/PassedTest.h"

class PassedTestModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit PassedTestModel(const PassedTest &passedTest, QObject *parent = nullptr);

    //  :: QAbstractListModel ::
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //  :: Accessors ::
    const PassedTest &getPassedTest() const;
    void setPassedTest(const PassedTest &passedTest);

    int getTestId() const;
    QString getPassedTestName() const;
    uint getNumberOfPasses() const;

    ScaleStatistics getScaleStatistics(const QModelIndex &index) const;

private:
    PassedTest m_passedTest;
};
