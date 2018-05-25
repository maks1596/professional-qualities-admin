#include "AutorizationModel.h"

#include "Entities/AutorizationData/AutorizationData.h"
#include "Requester/Requester.h"

//  :: Constants ::

const QString AUTORIZE_AS_ADMIN = "autorization/admin";

//  :: Lifecycle ::

AutorizationModel::AutorizationModel(QObject *parent/*= nullptr*/)
	: BaseModel(parent) { }

void AutorizationModel::autorizeAsAdmin(const QString &login,
										const QString &password) {
	autorizeAsAdmin({login, password});
}

void AutorizationModel::autorizeAsAdmin(const AutorizationData &data) {
	auto requester = makeRequester();
	connect(requester, SIGNAL(success()),
			SIGNAL(autorized()));
	requester->sendRequest(AUTORIZE_AS_ADMIN,
						   RequestType::POST,
						   data.toJson());
}

//  :: Public Methods ::
