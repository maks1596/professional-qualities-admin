#pragma once

#include "../PassedTestPreview/PassedTestPreview.h"
#include "../ScaleStatistics/ScaleStatistics.h"

class PassedTest : public PassedTestPreview {
public:
    //  :: Lifecycle ::
    PassedTest() = default;
    PassedTest(int id);

    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

    //  :: Accessors ::
    QList<ScaleStatistics> getScales() const;
    void setScales(const QList<ScaleStatistics> &scales);

private:
    QList<ScaleStatistics> m_scales;
};
