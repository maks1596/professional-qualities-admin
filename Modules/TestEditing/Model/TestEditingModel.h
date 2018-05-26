#pragma once

#include "BaseService/BaseService.h"

class ShortTestInfo;
class Test;

class TestEditingModel : public BaseService {
Q_OBJECT

public:
	TestEditingModel(QObject *parent = nullptr);

	void checkTestName(const QString testName) const;
	void putTest(const Test &test) const;
	void replaceTest(const Test &test) const;

signals:
	void testNameAlreadyTaken(const ShortTestInfo &shortTestInfo) const;
	void testNameIsFree() const;
	void testPut() const;
	void testIsUsed() const;
	void testDeleted() const;
	void testReplaced() const;

private slots:
	void jsonShortTestInfoReceived(const QJsonObject &jsonObject) const;
	void onTestDeleted(const Test &test) const;
};
