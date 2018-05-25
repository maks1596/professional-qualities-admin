#pragma once

#include <QScopedPointer>

#include "Serializable/Object/SerializableObject.h"

class AnswerOption;
typedef QList<AnswerOption> AnswerOptions;

class AnswerOption : public SerializableObject {
public:
	//  :: Lifecycle ::
	AnswerOption();
	AnswerOption(const QString &formulation);
    AnswerOption(const int &id, const QString &formulation);

	//  :: Copy ::
	AnswerOption(const AnswerOption &other);
	AnswerOption &operator=(const AnswerOption &other);

	//  :: Move ::
	AnswerOption(AnswerOption &&other);
	AnswerOption &operator=(AnswerOption &&other);

	//  :: Destructor ::
	virtual ~AnswerOption() noexcept override;

	//  :: Accessors ::
	int getId() const;
	void setId(const int &id);

    QString getFormulation() const;
    void setFormulation(const QString &formulation);

	/**
	 * @brief Метод проверяет пустая ли формулировка вопроса
	 * @return пустота формулировки вопроса
	 */
    bool isEmpty() const;

    //  :: Serializable ::
    virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};

bool operator==(const AnswerOption &lhs, const AnswerOption &rhs);
