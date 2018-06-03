#include "Requester.h"

#include <QBuffer>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QScopedPointer>

//  :: Constants ::

const QString HTTP_TEMPLATE = "http://%1:%2/api/%3";
const QString HTTPS_TEMPLATE = "https://%1:%2/api/%3";

const QString KEY_QNETWORK_REPLY_ERROR = "QNetworkReplyError";
const QString KEY_CONTENT_NOT_FOUND = "ContentNotFoundError";

// :: Private function headers ::

QByteArray jsonToByteArray(const QJsonObject &json);
QJsonDocument parseReply(QNetworkReply *reply);

// :: Implementation ::

struct Requester::Implementation {
    QNetworkAccessManager networkAccessManager;
    QString host;
    uint port;
    QScopedPointer<QSslConfiguration> sslConfiguration;
    QString pathTemplate;
};

//  :: Lifecycle ::

Requester::Requester(const QString& host, uint port,
					 QSslConfiguration *sslConfiguration)
	: pimpl(new Implementation())
{
    connect(&pimpl->networkAccessManager, &QNetworkAccessManager::finished,
            this, &Requester::onReplyReceived);
	init(host, port, sslConfiguration);
}

Requester::~Requester() {
    delete pimpl;
}

//  :: Public methods ::

void Requester::init(const QString& host, uint port,
					 QSslConfiguration *sslConfiguration/*= nullptr*/) {
    pimpl->host = host;
    pimpl->port = port;
    pimpl->sslConfiguration.reset(sslConfiguration);

    if (sslConfiguration) {
        pimpl->pathTemplate = HTTPS_TEMPLATE;
    } else {
        pimpl->pathTemplate = HTTP_TEMPLATE;
    }
}

void Requester::sendRequest(const QString &api, RequestType type,
							const QJsonObject &json) {
	QNetworkRequest request = createRequest(api);
	auto byteArray = jsonToByteArray(json);

	switch (type) {
	case RequestType::POST: {
		pimpl->networkAccessManager.post(request, byteArray);
	} break;

	case RequestType::PUT: {
		pimpl->networkAccessManager.put(request, byteArray);
	} break;

	case RequestType::GET: {
		pimpl->networkAccessManager.get(request);
	} break;

	case RequestType::DELET: {
		if (byteArray.isEmpty()) {
			pimpl->networkAccessManager.deleteResource(request);
		} else {
			sendCustomRequest(request, "DELETE", byteArray);
		}
	} break;

	case RequestType::PATCH: {
		sendCustomRequest(request, "PATCH", byteArray);
	} break;
	}
}

//  :: Private slots ::

void Requester::onReplyReceived(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
		QJsonDocument jsonDocument = parseReply(reply);
		if (jsonDocument.isObject()) {
			emit success(jsonDocument.object());
		} else if (jsonDocument.isArray()) {
			emit success(jsonDocument.array());
		} else {
			emit success();
		}
	} else {
		qDebug() << "Reply error: " << reply->error()
				 << "\nMessage: " << reply->errorString();
        emit failure(reply->errorString());
    }
    reply->deleteLater();
}

//  :: Private methods ::

QNetworkRequest Requester::createRequest(const QString &api) {
    QNetworkRequest request;
    QString url = pimpl->pathTemplate.arg(pimpl->host)
                                     .arg(pimpl->port)
                                     .arg(api);
    request.setUrl(QUrl(url));
	request.setRawHeader("Content-Type", "application/json");

    // здесь прописываются все необходимые заголовки запроса
    if (!pimpl->sslConfiguration.isNull()) {
        request.setSslConfiguration(*pimpl->sslConfiguration);
    }

    return request;
}

QNetworkReply* Requester::sendCustomRequest(QNetworkRequest &request,
                                            const QString &type,
											const QByteArray &byteArray) {
	auto buffer = new QBuffer();
	buffer->buffer() = byteArray;
    QNetworkReply *reply = nullptr;

	if (buffer->open(QIODevice::ReadOnly)) {
		reply = pimpl->networkAccessManager
				.sendCustomRequest(request, type.toUtf8(), buffer);
		connect(reply, &QNetworkReply::finished,
				buffer, &QBuffer::deleteLater);
	} else {
		buffer->deleteLater();
	}
	return reply;
}

//  :: Private functions ::

inline
QByteArray jsonToByteArray(const QJsonObject &json) {
	return QJsonDocument(json).toJson();
}

QJsonDocument parseReply(QNetworkReply *reply) {
	auto replyByteArray = reply->readAll();
	if (replyByteArray.isEmpty()) {  // Всё ок - парсить нечего
		return QJsonDocument();
	}

    QJsonParseError parseError;
	auto jsonDoc = QJsonDocument::fromJson(replyByteArray, &parseError);

	if(parseError.error != QJsonParseError::NoError){
		qDebug() << replyByteArray;
        qWarning() << "Json parse error: " << parseError.errorString();
    }
	return jsonDoc;
}
