#pragma once

#include <QScopedPointer>

#include "Serializable/Object/SerializableObject.h"

class Scale;
typedef QList<Scale> Scales;

class QString;

class EvaluationMap;
class Key;
class GeneralAnswerOptionsKey;
class UniqueAnswerOptionsKey;

/**
 * @brief Шкала для оценивания какого-либо качества тестируемого
 */
class Scale : public SerializableObject {
public:
	//  :: Lifecycle ::
	//  :: Constructors ::
	Scale();
	Scale(const int &id);
	Scale(const QString &name);
	Scale(const int &id, const QString &name);

	//  :: Copy ::
	Scale(const Scale &other);
	Scale &operator=(const Scale &other);

	//  :: Move ::
	Scale(Scale &&other);
	Scale &operator=(Scale &&other);

	//  :: Destructor ::
	virtual ~Scale() noexcept override;

	//  :: Accessors ::
	int getId() const;
	void setId(const int &id);

    QString getName() const;
    void setName(const QString &getName);

	Key *getKey();
	GeneralAnswerOptionsKey *getGeneralAnswerOptionsKey();
	UniqueAnswerOptionsKey *getUniqueAnswerOptionsKey();

	EvaluationMap *getEvaluationMap();

    //  :: Serializable ::
	virtual QJsonObject toJson() const override;
    virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};

//  :: Functions ::

bool operator==(const Scale &lhs, const Scale &rhs);
