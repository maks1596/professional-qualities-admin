#include "TestsModel.h"

#include <QJsonArray>
#include <QJsonValue>

#include "Entities/ShortTestInfo/ShortTestInfo.h"
#include "Entities/Test/Test.h"
#include "Requester/Requester.h"

//  :: Constants ::

const QString GET_TESTS_API = "tests";
const QString GET_TEST_API = "tests/with-scales/%1";
const QString DELETE_TEST_API = "tests/%1";

//  :: Lifeccyle ::

TestsModel::TestsModel(QObject *parent/*= nullptr*/)
	: BaseService(parent) {}

//  :: Public methods ::

void TestsModel::getTests() const {
	auto requester = makeRequester();
	connect(requester, SIGNAL(success(QJsonArray)),
			SLOT(jsonTestsGot(QJsonArray)));
	requester->sendRequest(GET_TESTS_API);
}

void TestsModel::getTest(int id) const {
	auto requester = makeRequester();
	connect(requester, SIGNAL(success(QJsonObject)),
			SLOT(jsonTestGot(QJsonObject)));
	requester->sendRequest(GET_TEST_API.arg(id));
}

void TestsModel::deleteTest(int id) const {
	auto requester = makeRequester();
	connect(requester, SIGNAL(success()),
			SIGNAL(testDeleted()));

	disconnect(requester, &Requester::failure,
			   this, &BaseService::error);
	connect(requester, &Requester::failure,
			this, &TestsModel::testIsUsed);

	requester->sendRequest(DELETE_TEST_API.arg(id),
						   RequestType::DELET);
}

//  :: Private slots ::

void TestsModel::jsonTestsGot(const QJsonArray &jsonArray) {
	QList<ShortTestInfo> tests;
	for (const auto &jsonShortTestInfo : jsonArray) {
		if (jsonShortTestInfo.isObject()) {
			QJsonObject jsonObject = jsonShortTestInfo.toObject();
			ShortTestInfo test;
			test.initWithJsonObject(jsonObject);
			tests.append(test);
		}
	}
	emit testsGot(tests);
}

void TestsModel::jsonTestGot(const QJsonObject &jsonObject) {
	Test test;
	test.initWithJsonObject(jsonObject);
	emit testGot(test);
}
