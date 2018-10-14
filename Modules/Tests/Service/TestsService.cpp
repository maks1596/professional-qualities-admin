#include "TestsService.h"

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

TestsService::TestsService(QObject *parent/*= nullptr*/)
	: BaseService(parent) {}

//  :: Public methods ::

void TestsService::getTests() const {
	auto requester = makeRequesterWithDefaultErrorOutput();
	connect(requester, SIGNAL(success(QJsonArray)),
			SLOT(jsonTestsGot(QJsonArray)));
	requester->sendRequest(GET_TESTS_API);
}

void TestsService::getTest(int id) const {
	auto requester = makeRequesterWithDefaultErrorOutput();
	connect(requester, SIGNAL(success(QJsonObject)),
			SLOT(jsonTestGot(QJsonObject)));
	requester->sendRequest(GET_TEST_API.arg(id));
}

void TestsService::removeTest(int id) const {
    auto requester = makeRequester();

    connect(requester, SIGNAL(success()),
			SIGNAL(testDeleted()));
	connect(requester, &Requester::failure,
            this, &TestsService::testIsUsed);

	requester->sendRequest(DELETE_TEST_API.arg(id),
						   RequestType::DELET);
}

//  :: Private slots ::

void TestsService::jsonTestsGot(const QJsonArray &jsonArray) {
    auto tests = serializableObjectsFromJsonArray<QList, ShortTestInfo>(jsonArray);
	emit testsGot(tests);
}

void TestsService::jsonTestGot(const QJsonObject &jsonObject) {
    auto test = makeWithJsonObject<Test>(jsonObject);
	emit testGot(test);
}
