#pragma once

#include <QAbstractTableModel>

#include "Entities/PassedTestPreview/PassedTestPreview.h"

class PassedTestsModel : public QAbstractTableModel {
public:
    PassedTestsModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QList<PassedTestPreview> m_previews;
};
