#pragma once

#include <QVariant>
#include <QString>

class NamedValue {
public:

    //  :: Lifecycle ::

    NamedValue(const QString &name = QString(),
               const QVariant &value = QVariant());

    //  :: Accessors ::

    const QString &getName() const;
    void setName(const QString &name);

    const QVariant &getValue() const;
    void setValue(const QVariant &value);

private:
    QString m_name;
    QVariant m_value;
};

bool operator ==(const NamedValue &lhs, const NamedValue &rhs);
