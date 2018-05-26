#pragma once

#include "QObject"

class Requester;
class QString;

class BaseService : public QObject {
    Q_OBJECT

public:
	BaseService(QObject *parent = nullptr);

signals:
	void error(const QString &message);

protected:
	Requester *makeRequester() const;
};
