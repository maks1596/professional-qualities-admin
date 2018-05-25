#pragma once

#include "BaseModel/BaseModel.h"

class AutorizationData;

class AutorizationModel : public BaseModel {
Q_OBJECT
public:
	AutorizationModel(QObject *parent = nullptr);

	void autorizeAsAdmin(const QString &login, const QString &password);
	void autorizeAsAdmin(const AutorizationData &data);

signals:
	void autorized();
};
