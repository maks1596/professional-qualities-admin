#pragma once

#include "QObject"

class Requester;
class QString;

class BaseModel : public QObject {
Q_OBJECT

public:
	BaseModel(QObject *parent = nullptr);

signals:
	void error(const QString &message);

protected:
	Requester *makeRequester() const;
};
