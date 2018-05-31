#include "Indicator.h"

#include "Tree.h"

//  :: Constants ::

const QString NAME_JSON_KEY = "name";
const QString VALUE_JSON_KEY = "value";

//  :: Serilizable ::

QJsonObject Indicator::toJson() const {
    QJsonObject json;
    json[NAME_JSON_KEY] = getName();
    json[VALUE_JSON_KEY] = getValue();
    return json;
}

void Indicator::initWithJsonObject(const QJsonObject &json) {
    if (json.contains(NAME_JSON_KEY) && json[NAME_JSON_KEY].isString()) {
        setName(json[NAME_JSON_KEY].toString());
    }
    if (json.contains(VALUE_JSON_KEY) && json[VALUE_JSON_KEY].isDouble()) {
        setValue(json[VALUE_JSON_KEY].toDouble());
    }
}

//  :: Public accessors ::
//  :: Name ::
QString Indicator::getName() const {
    return m_name;
}
void Indicator::setName(const QString &name) {
    m_name = name;
}

//  :: Value ::
double Indicator::getValue() const {
    return m_value;
}
void Indicator::setValue(double value) {
    m_value = value;
}

//  :: Public methods ::

Tree::NodePtr<Indicator> Indicator::toTreeNodePtr(const Tree::NodePtr<Indicator> &parent) const {
    Tree::NodePtr<Indicator> node(new Tree::Node<Indicator>);
    node->data = *this;
    node->parent = parent;
    return node;
}

//  :: Public functions ::

bool operator==(const Indicator &lhs, const Indicator &rhs) {
    return lhs.getName() == rhs.getName() &&
            lhs.getValue() == rhs.getValue();
}
