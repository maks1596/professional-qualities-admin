#pragma once

#include "Serializable/Object/SerializableObject.h"
#include "Tree.h"

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

    Tree::NodePtr<Indicator> toTreeNodePtr(const Tree::NodePtr<Indicator> &parent) const;

private:
    QString m_name;
    double m_value = 0.0;
};

bool operator==(const Indicator &lhs, const Indicator &rhs);
