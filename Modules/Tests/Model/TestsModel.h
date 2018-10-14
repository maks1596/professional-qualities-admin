#pragma once

#include <QAbstractTableModel>
#include <QList>

class ShortTestInfo;

class TestsModel : public QAbstractTableModel {
public:
    TestsModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    const QList<ShortTestInfo> &getTests() const;
    void setTests(const QList<ShortTestInfo> &tests);

    ShortTestInfo getTest(uint index) const;
    int getTestId(uint index) const;
    int getRemoveColumnIndex() const;

private:
    QList<ShortTestInfo> m_tests;
};
