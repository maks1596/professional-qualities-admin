#pragma once

#include "../CorrelationValue/CorrelationValue.h"
#include "Serializable/Object/SerializableObject.h"

class GroupCorrelations: public SerializableObject {
public:

    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

    //  :: Accessors ::

    const QString &getGroupName() const;
    void setGroupName(const QString &groupName);

    const QList<CorrelationValue> &getCorrelationValues() const;
    void setCorrelationValues(const QList<CorrelationValue> &correlationValues);

private:
    QString m_groupName;
    QList<CorrelationValue> m_correlationValues;
};
