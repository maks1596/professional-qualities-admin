#pragma once

#include <QTableView>

class CorrelationsForm : public QTableView {
    Q_OBJECT
public:
    explicit CorrelationsForm(QWidget *parent = nullptr)
        : QTableView(parent) {}

signals:
    void error(const QString &errorMessage);
};
