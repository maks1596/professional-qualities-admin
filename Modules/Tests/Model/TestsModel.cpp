#include "TestsModel.h"

#include <QJsonArray>
#include <QJsonValue>

#include "Entities/ShortTestInfo/ShortTestInfo.h"
#include "Entities/Test/Test.h"
#include "Requester/Requester.h"
#include "JsonArraySerialization.h"

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
    auto tests = serializableObjectsFromJsonArray<QList, ShortTestInfo>(jsonArray);
	emit testsGot(tests);
}

void TestsModel::jsonTestGot(const QJsonObject &jsonObject) {
    auto test = makeWithJsonObject<Test>(jsonObject);
	emit testGot(test);
}
