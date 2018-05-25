#include "Entity.h"

//  :: Constatnts ::

const QString ID_JSON_KEY = "id";

//  :: Implementation

struct Entity::Implementation {
	int id = 0;
};

//  :: Lifecycle ::
//  :: Constructors ::
Entity::Entity(int id/*= 0*/)
	: pimpl(new Implementation())
{
	setId(id);
}

//  :: Copy ::
Entity::Entity(const Entity &other)
	: pimpl(new Implementation(*other.pimpl))
{ }
Entity &Entity::operator=(const Entity &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
Entity::Entity(Entity &&other) : pimpl(other.pimpl.take()) {}
Entity &Entity::operator=(Entity &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
Entity::~Entity() {}

//  :: Accessors ::

int Entity::getId() const {
	return pimpl->id;
}
void Entity::setId(int id) {
	pimpl->id = id;
}

//  :: Serializable ::

QJsonObject Entity::toJson() const {
	QJsonObject json;
	json[ID_JSON_KEY] = getId();
	return json;
}

void Entity::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(ID_JSON_KEY) && json[ID_JSON_KEY].isDouble()) {
		setId(json[ID_JSON_KEY].toInt());
	}
}
