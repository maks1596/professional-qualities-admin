#include "PassedTestsModel.h"

//  :: Constants ::

enum ColumnIndex {
    NAME_COLUMN_INDEX,
    NUMBER_OF_PASSES_COLUMN_INDEX,
    NUMBER_OF_COLUMNS
};

const QStringList kHorizontalHeaders {
    "Название теста",
    "Пройден"
};

//  :: Lifecycle ::

PassedTestsModel::PassedTestsModel(QObject *parent/*= nullptr*/)
    : QAbstractTableModel(parent) {
    m_previews << PassedTestPreview(1, "1", 1)
               << PassedTestPreview(2, "2", 2)
               << PassedTestPreview(3, "3", 3);
}

//  :: QAbstractTableModel ::

int PassedTestsModel::rowCount(const QModelIndex &) const {
    return m_previews.size();
}

int PassedTestsModel::columnCount(const QModelIndex &) const {
    return NUMBER_OF_COLUMNS;
}

QVariant PassedTestsModel::data(const QModelIndex &index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole) {
        auto preview = m_previews[index.row()];
        switch (index.column()) {
        case NAME_COLUMN_INDEX:
            return preview.getName();
        case NUMBER_OF_PASSES_COLUMN_INDEX:
            return preview.getNumberOfPasses();
        }
    }
    return QVariant();
}

QVariant PassedTestsModel::headerData(int section,
                                      Qt::Orientation orientation,
                                      int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            return kHorizontalHeaders[section];
        } else {
            return section + 1;
        }
    }
    return QVariant();
}
