#pragma once

#include <QObject>

class AddUserOutput : public QObject {
    Q_OBJECT
public:
    explicit AddUserOutput(QObject *parent = nullptr);

signals:
    void userAdded();
    void error(const QString &errorMessage);
};
