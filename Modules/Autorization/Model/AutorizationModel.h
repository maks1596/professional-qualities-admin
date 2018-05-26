#pragma once

#include "BaseService/BaseService.h"

class AutorizationData;

class AutorizationModel : public BaseService {
Q_OBJECT
public:
	AutorizationModel(QObject *parent = nullptr);

	void autorizeAsAdmin(const QString &login, const QString &password);
	void autorizeAsAdmin(const AutorizationData &data);

signals:
	void autorized();
};
