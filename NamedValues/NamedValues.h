#pragma once

#include <QString>
#include <QVariantList>

class NamedValues {
public:

    //  :: Lifecycle ::

    NamedValues() = default;
    NamedValues(const QString &name);
    NamedValues(const QString &name,
                std::initializer_list<QVariant> values);

    //  :: Accessors ::

    QString getName() const;
    void setName(const QString &name);

    const QVariantList &getValues() const;
    void setValues(const QVariantList &values);

    const QVariant &getValue(ptrdiff_t index) const;

    //  :: Indexators ::

    const QVariant &operator[](ptrdiff_t index) const;
    QVariant &operator[](ptrdiff_t index);

    //  :: Methods ::

    void appendValue(const QVariant &value);

    bool removeValue(const QVariant &value);
    void removeValue(ptrdiff_t index);


private:
    QString m_name;
    QVariantList m_values;
};

bool operator ==(const NamedValues &lhs, const NamedValues &rhs);
