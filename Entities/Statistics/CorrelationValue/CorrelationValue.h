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

    QString getFullName() const;
    void setFullName(const QString &fullName);

    const QVariant &getValue() const;
    void setValue(const QVariant &value);

private:
    QString m_name;
    QString m_fullName;
    QVariant m_value;
};
