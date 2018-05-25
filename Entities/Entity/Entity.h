#pragma once

#include <QScopedPointer>

#include "Serializable/Object/SerializableObject.h"

class Entity : SerializableObject {
public:
	//  :: Lifecycle ::
	//  :: Constructors ::
	Entity(int id = 0);

	//  :: Copy ::
	Entity(const Entity &other);
	Entity &operator=(const Entity &other);

	//  :: Move ::
	Entity(Entity &&other);
	Entity &operator=(Entity &&other);

	//  :: Destructor ::
	virtual ~Entity() noexcept;

	//  :: Accessors ::
	int getId() const;
	void setId(int id);

	//  :: Serializable ::
	virtual QJsonObject toJson() const override;
	virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
