#pragma once

#include <QScopedPointer>

#include "Serializable/Object/SerializableObject.h"

class AutorizationData : public SerializableObject {
public:

	//  :: Lifecycle ::
	//  :: Constructors ::
	AutorizationData();
	AutorizationData(const QString login, const QString password);

	//  :: Copy ::
	AutorizationData(const AutorizationData &other);
	AutorizationData &operator=(const AutorizationData &other);

	//  :: Move ::
	AutorizationData(AutorizationData &&other);
	AutorizationData &operator=(AutorizationData &&other);

	//  :: Destructor ::
	virtual ~AutorizationData() noexcept;

	//  :: Accessors ::

	QString getLogin() const;
	void setLogin(const QString &login);

	QString getPassword() const;
	void setPassword(const QString &password);

	//  :: Serializable ::
	virtual QJsonObject toJson() const override;
	virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
