#pragma once

#include "Serializable/Object/SerializableObject.h"

class ScaleStatistics : public SerializableObject {
public:
    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;
};
