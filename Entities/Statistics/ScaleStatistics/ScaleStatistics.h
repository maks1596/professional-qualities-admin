#pragma once

#include "../ResultStatistics/ResultStatistics.h"
#include "Serializable/Object/SerializableObject.h"

class ScaleStatistics : public SerializableObject {
public:
    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

    //  :: Accessors ::

    int getId() const;
    void setId(int id);

    QString getName() const;
    void setName(const QString &name);

    QList<ResultStatistics> getProgrammersResults() const;
    void setProgrammersResults(const QList<ResultStatistics> &programmersResults);

    QList<ResultStatistics> getNonProgrammersResults() const;
    void setNonProgrammersResults(const QList<ResultStatistics> &nonProgrammersResults);

private:
    int m_id;
    QString m_name;
    QList<ResultStatistics> m_programmersResults;
    QList<ResultStatistics> m_nonProgrammersResults;
};
