#ifndef ANSWEROPTION_H
#define ANSWEROPTION_H

#include <QString>
#include <QList>

#include "Serializable/Serializable.h"

class AnswerOption;
typedef QList<AnswerOption> AnswerOptions;

class AnswerOption : public Serializable {

public:
    AnswerOption(const QString &formulation = "");
    AnswerOption(const int &id, const QString &formulation);

    int getID() const;
    void setID(const int &id);

    QString getFormulation() const;
    void setFormulation(const QString &formulation);

    bool isEmpty() const;

    //  :: Serializable ::
    virtual QJsonObject toJsonObject() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

private:
    int m_id;
    QString m_formulation;
};

bool operator==(const AnswerOption &lhs, const AnswerOption &rhs);

#endif // ANSWEROPTION_H
