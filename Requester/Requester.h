#pragma once

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QSslConfiguration>
#include <QJsonObject>

#include "RequestType.h"

/**
 * @brief Класс обеспечивает Rest API
 *
 * Реализация взята с https://habrahabr.ru/post/314932/
 */
class Requester : public QObject {
Q_OBJECT

public:
	Requester(const QString& host = "localhost", uint port = 5432,
			  QSslConfiguration *sslConfiguration = nullptr);
    virtual ~Requester() noexcept;

    /**
     * @brief Метод инициализирует объект класса
     * @param host - адрес хоста
     * @param port - номер порта
     * @param sslConfiguration - ssl конфигурация для доступа по https
     */
	void init(const QString& host, uint port,
			  QSslConfiguration *sslConfiguration = nullptr);

    /**
     * @brief Метод отправляет запрос на сервер
     * @param api - API запроса
     * @param type - тип запроса
     * @param json - отправляемый объект в формате JSON
     */
    void sendRequest(const QString &api,
                     RequestType type = RequestType::GET,
                     const QJsonObject &json = QJsonObject());

signals:
    void success(const QJsonObject &response);
	void success(const QJsonArray &response);
	void success();

    void failure(const QString &errorString);

private slots:
    void onReplyReceived(QNetworkReply *reply);

private:
    QNetworkRequest createRequest(const QString &apiStr);

	QNetworkReply* sendCustomRequest(QNetworkRequest &request,
									 const QString &type,
									 const QByteArray &byteArray);

    struct Implementation;
    Implementation *pimpl;
};
