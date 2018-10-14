#include "TestsModel.h"

#include "Entities/ShortTestInfo/ShortTestInfo.h"

//  :: Constants ::

enum ColumnIndex {
    NAME_COLUMN_INDEX,
    REMOVE_COLUMN_INDEX,
    COLUMNS_COUNT
};

//  :: Lifecycle ::

TestsModel::TestsModel(QObject *parent)
    : QAbstractTableModel(parent)
{ }

//  :: QAbstractTableModel ::

int TestsModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_tests.size();
}

int TestsModel::columnCount(const QModelIndex &) const {
    return COLUMNS_COUNT;
}

QVariant TestsModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole && index.isValid()) {
        auto test = m_tests[index.row()];

        switch (index.column()) {
        case NAME_COLUMN_INDEX:
            return test.getName();
        case REMOVE_COLUMN_INDEX:
            return "Удалить";
        }
    }
    return QVariant();
}

QVariant TestsModel::headerData(int section,
                                Qt::Orientation orientation,
                                int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            if (section == NAME_COLUMN_INDEX) {
                return "Название теста";
            }
        } else {
            return section + 1;
        }
    }
    return QVariant();
}

//  :: Public accessors ::

const QList<ShortTestInfo> &TestsModel::getTests() const {
    return m_tests;
}
void TestsModel::setTests(const QList<ShortTestInfo> &tests) {
    if (m_tests.isEmpty()) {
        beginResetModel();
        m_tests = tests;
        endResetModel();
    } else {
        updateData(tests);
    }
    emitAllDataChanged();
}

//  :: Public methods ::

ShortTestInfo TestsModel::getTest(int index) const {
    if (index < m_tests.size()) {
        return m_tests[index];
    }
    return ShortTestInfo();
}

int TestsModel::getTestId(int index) const {
    return getTest(index).getId();
}

int TestsModel::getRemoveColumnIndex() const {
    return REMOVE_COLUMN_INDEX;
}

//  :: Private methods ::

inline
void TestsModel::updateData(const QList<ShortTestInfo> &tests) {
    if (tests.size() < m_tests.size()) {
        beginRemoveRows(QModelIndex(), tests.size(), m_tests.size() - 1);
        m_tests = tests;
        endRemoveRows();
    } else if (tests.size() > m_tests.size()) {
        beginInsertRows(QModelIndex(), m_tests.size(), tests.size() - 1);
        m_tests = tests;
        endInsertRows();
    } else {
        m_tests = tests;
    }
}

inline
void TestsModel::emitAllDataChanged() {
    emit dataChanged(index(0, 0),
                     index(m_tests.size() - 1,
                           COLUMNS_COUNT - 1));
}
