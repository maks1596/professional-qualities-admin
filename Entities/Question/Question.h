#pragma once

#include <QScopedPointer>

#include "Entities/AnswerOption/AnswerOption.h"
#include "Serializable/Object/SerializableObject.h"

class Question;
typedef QList<Question> Questions;

class Question : public SerializableObject {
public:
	//  :: Lifecycle ::
	//  :: Constructors ::
	Question();
	Question(const QString &formulation);

	//  :: Copy ::
	Question(const Question &other);
	Question &operator=(const Question &other);

	//  :: Move ::
	Question(Question &&other);
	Question &operator=(Question &&other);

	//  :: Destructor ::
	virtual ~Question() noexcept override;

	//  :: Accessors ::
	int getId() const;
	void setId(const int &id);

    QString getFormulation() const;
    void setFormulation(const QString &formualtion);

    AnswerOptions getAnswerOptions() const;
	AnswerOptions *getAnswerOptions();
    void setAnswerOptions(const AnswerOptions &answerOptions);

	void addAnswerOption(AnswerOption answerOption);

    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
