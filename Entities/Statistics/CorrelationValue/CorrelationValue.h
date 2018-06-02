#pragma once

#include "Serializable/Object/SerializableObject.h"

class CorrelationValue : public SerializableObject {
public:

    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

    //  :: Accessors ::

    const QString &getName() const;
    void setName(const QString &name);

    const QVariant &getValue() const;
    void setValue(const QVariant &value);

private:
    QString m_name;
    QVariant m_value;
};
