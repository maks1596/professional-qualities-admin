#pragma once

#include "Serializable/Object/SerializableObject.h"

class PassedTestPreview : SerializableObject {
public:
    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

    //  :: Public accessors ::

    int getId() const;
    void setId(int id);

    QString getName() const;
    void setName(const QString &name);

    uint getNumberOfPasses() const;
    void setNumberOfPasses(uint numberOfPasses);

private:
    int m_id;
    QString m_name;
    uint m_numberOfPasses;
};
