#pragma once

#include "Serializable/Object/SerializableObject.h"
#include "Tree.h"

class NamedValue;

class Indicator : public SerializableObject {
public:
    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

    //  :: Accessors ::

    QString getName() const;
    void setName(const QString &name);

    double getValue() const;
    void setValue(double value);

    Tree::NodePtr<NamedValue> toTreeNodePtr(const Tree::NodePtr<NamedValue> &parent) const;

private:
    QString m_name;
    double m_value = 0.0;
};
