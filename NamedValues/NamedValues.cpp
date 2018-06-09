#include "NamedValues.h"

//  :: Lifecycle ::

NamedValues::NamedValues(const QString &name)
    : m_name(name)
{ }

NamedValues::NamedValues(const QString &name,
                         std::initializer_list<QVariant> values)
    : m_name(name),
      m_values(values)
{ }

//  :: Public accessors ::
//  :: Name ::
QString NamedValues::getName() const {
    return m_name;
}
void NamedValues::setName(const QString &name) {
    m_name = name;
}

//  :: Values ::
const QVariantList &NamedValues::getValues() const {
    return m_values;
}
void NamedValues::setValues(const QVariantList &values) {
    m_values = values;
}

const QVariant &NamedValues::getValue(ptrdiff_t index) const {
    return m_values.at(index);
}

//  :: Indexators ::

const QVariant &NamedValues::operator[](ptrdiff_t index) const {
    return m_values[index];
}

QVariant &NamedValues::operator[](ptrdiff_t index) {
    return m_values[index];
}

//  :: Public methods ::

void NamedValues::appendValue(const QVariant &value) {
    m_values.append(value);
}

bool NamedValues::removeValue(const QVariant &value) {
    return m_values.removeOne(value);
}

void NamedValues::removeValue(ptrdiff_t index) {
    m_values.removeAt(index);
}

//  :: Public functions ::

bool operator ==(const NamedValues &lhs, const NamedValues &rhs) {
    return     lhs.getName() == rhs.getName()
            && lhs.getValues() == rhs.getValues();
}
