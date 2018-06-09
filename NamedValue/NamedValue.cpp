#include "NamedValue.h"

//  :: Lifecycle ::

NamedValue::NamedValue(const QString &name,
                       const QVariant &value) {
    setName(name);
    setValue(value);
}

//  :: Public accessors ::
//  :: Name ::
const QString &NamedValue::getName() const {
    return m_name;
}
void NamedValue::setName(const QString &name) {
    m_name = name;
}

//  :: Value ::
const QVariant &NamedValue::getValue() const {
    return m_value;
}
void NamedValue::setValue(const QVariant &value) {
    m_value = value;
}

//  :: Public functions

bool operator ==(const NamedValue &lhs, const NamedValue &rhs) {
    return lhs.getName() == rhs.getName() &&
            lhs.getValue() == rhs.getValue();
}
