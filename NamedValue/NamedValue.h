#pragma once

#include <QVariant>
#include <QString>

struct NamedValue {
    QString name;
    QVariant value;
};

bool operator ==(const NamedValue &lhs, const NamedValue &rhs);
