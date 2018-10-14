#pragma once

#include <QObject>

class EntitiesOutput : public QObject {
    Q_OBJECT
public:
    explicit EntitiesOutput(QObject *parent = nullptr);

signals:
    void statusMessage(const QString &message);
    void error(const QString &errorMessage);
};
