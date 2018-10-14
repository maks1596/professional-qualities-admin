#pragma once

#include <QObject>

class EditUserOutput : public QObject {
    Q_OBJECT
public:
    explicit EditUserOutput(QObject *parent = nullptr);

signals:
    void error(const QString &errorMessage);
};
