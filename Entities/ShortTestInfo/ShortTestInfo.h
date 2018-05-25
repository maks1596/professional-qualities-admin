#pragma once

#include <QScopedPointer>

#include "Entities/Entity/Entity.h"

class QString;

/**
 * @brief Краткая информация о тесте: ID и имя
 */
class ShortTestInfo : public Entity {
public:
	//  :: Lifecycle ::
	//  :: Constructors ::
	ShortTestInfo(int id = 0, const QString &name = "");

	//  :: Copy ::
	ShortTestInfo(const ShortTestInfo &other);
	ShortTestInfo &operator=(const ShortTestInfo &other);

	//  :: Move ::
	ShortTestInfo(ShortTestInfo &&other);
	ShortTestInfo &operator=(ShortTestInfo &&other);

	//  :: Destructor ::
	virtual ~ShortTestInfo() noexcept override;

	//  :: Accessors ::
	QString getName() const;
	void setName(const QString &name);

	//  :: Serializable ::
	virtual QJsonObject toJson() const override;
	virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
