#pragma once

#include <QTableView>

class CorrelationsForm : public QTableView {
    Q_OBJECT
public:
    explicit CorrelationsForm(QWidget *parent = nullptr);

    void setModel(QAbstractItemModel *model) override;

signals:
    void error(const QString &errorMessage);
};
