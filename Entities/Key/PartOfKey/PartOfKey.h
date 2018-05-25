#pragma once

#include <QScopedPointer>

#include "Indexes.h"
#include "Serializable/Object/SerializableObject.h"

class PartOfGeneralAnswerOptionsKey;
class PartOfUniqueAnswerOptionsKey;

/**
 * @brief Класс представляет собой часть оценочного ключа -
 *        объединение из индексов вопросоа, вариантов ответа и количества баллов
 */
class PartOfKey : public SerializableObject {
public:
	//  :: Lifecycle ::
	//  :: Constructors ::
	PartOfKey();

	//  :: Copy ::
	PartOfKey(const PartOfKey &other);
	PartOfKey &operator=(const PartOfKey &other);

	//  :: Move ::
	PartOfKey(PartOfKey &&other);
	PartOfKey &operator=(PartOfKey &&other);

	//  :: Destructor ::
	virtual ~PartOfKey() noexcept override;

	//  :: Accessors ::
	uint getPoints() const;
	void setPoints(const uint &points);

	//  :: Transformations ::
	PartOfGeneralAnswerOptionsKey *toPartOfGeneralAnswerOptionsKey();
	const PartOfGeneralAnswerOptionsKey *toPartOfGeneralAnswerOptionsKey() const;

	PartOfGeneralAnswerOptionsKey *toPOGAOK();
	const PartOfGeneralAnswerOptionsKey *toPOGAOK() const;


	PartOfUniqueAnswerOptionsKey *toPartOfUniqueAnswerOptionsKey();
	const PartOfUniqueAnswerOptionsKey *toPartOfUniqueAnswerOptionsKey() const;

	PartOfUniqueAnswerOptionsKey *toPOUAOK();
	const PartOfUniqueAnswerOptionsKey *toPOUAOK() const;


	//  :: Serializable ::
	virtual QJsonObject toJson() const override;
	virtual void initWithJsonObject(const QJsonObject &json) override;

protected:
	//  :: Accessors ::
	Indexes &getInternalQuestionIndexes();
	const Indexes &getInternalQuestionIndexes() const;

	Indexes &getInternalAnswerOptionIndexes();
	const Indexes &getInternalAnswerOptionIndexes() const;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
