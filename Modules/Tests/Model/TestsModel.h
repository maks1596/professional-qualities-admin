#pragma once

#include "BaseService/BaseService.h"

class ShortTestInfo;
class Test;

class TestsModel : public BaseService {
Q_OBJECT

public:
	TestsModel(QObject *parent = nullptr);

	void getTests() const;
	void getTest(int id) const;
	void deleteTest(int id) const;

signals:
	void testsGot(const QList<ShortTestInfo> &tests);
	void testGot(const Test &test);
	void testDeleted();
	void testIsUsed();

private slots:
	void jsonTestsGot(const QJsonArray &jsonArray);
	void jsonTestGot(const QJsonObject &jsonObject);
};
