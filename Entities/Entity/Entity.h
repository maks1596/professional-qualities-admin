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
    Entity(Entity &&other) noexcept;
    Entity &operator=(Entity &&other) noexcept;

	//  :: Destructor ::
     ~Entity() noexcept override;

	//  :: Accessors ::
	int getId() const;
	void setId(int id);

	//  :: Serializable ::
     QJsonObject toJson() const override;
     void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
