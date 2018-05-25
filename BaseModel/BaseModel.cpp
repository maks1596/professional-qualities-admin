#include "BaseModel.h"

#include "Requester/Requester.h"
#include "Configurator/Configurator.h"

BaseModel::BaseModel(QObject *parent/*= nullptr*/)
	: QObject(parent) {}

Requester *BaseModel::makeRequester() const {
	Requester *requester = new Requester(Configurator::getHostName(),
										 Configurator::getPort());

	connect(requester, SIGNAL(failure(QString)),
			this, SIGNAL(error(QString)));

	connect(requester, SIGNAL(success(QJsonObject)),
			requester, SLOT(deleteLater()));
	connect(requester, SIGNAL(success(QJsonArray)),
			requester, SLOT(deleteLater()));
	connect(requester, SIGNAL(success()),
			requester, SLOT(deleteLater()));
	connect(requester, SIGNAL(failure(QString)),
			requester, SLOT(deleteLater()));

	return requester;
}
