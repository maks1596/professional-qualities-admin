#include "TestEditingModel.h"

#include "Entities/ShortTestInfo/ShortTestInfo.h"
#include "Entities/Test/Test.h"
#include "Requester/Requester.h"

//  :: Constants ::

const QString GET_SHORT_TEST_INFO_API = "tests/short/by-name/%1";
const QString PUT_TEST_API = "tests";
const QString DELETE_TEST_API = "tests/%1";

//  :: Lifecycle ::

TestEditingModel::TestEditingModel(QObject *parent/*= nullptr*/)
	: BaseService(parent) { }

//  :: Public methods ::

void TestEditingModel::checkTestName(const QString &testName) const {
    auto requester = makeRequester();
	connect(requester, SIGNAL(success(QJsonObject)),
			SLOT(jsonShortTestInfoReceived(QJsonObject)));
	connect(requester, SIGNAL(failure(QString)),
			SIGNAL(testNameIsFree()));

	auto normalizedName = QString(testName).replace(' ', '_');
	requester->sendRequest(GET_SHORT_TEST_INFO_API
						   .arg(normalizedName));
}

void TestEditingModel::putTest(const Test &test) const {
	auto requester = makeRequesterWithDefaultErrorOutput();
	connect(requester, SIGNAL(success()),
			SIGNAL(testPut()));
	requester->sendRequest(PUT_TEST_API,
						   RequestType::PUT,
						   test.toJson());
}

void TestEditingModel::replaceTest(const Test &test) const {
    auto requester = makeRequester();

	connect(requester, SIGNAL(error(QString)),
			SIGNAL(testIsUsed()));

	connect(requester, SIGNAL(success()),
			SIGNAL(testDeleted()));
	connect(this, &TestEditingModel::testDeleted,
			[this, test](){onTestDeleted(test);});

	requester->sendRequest(DELETE_TEST_API
						   .arg(test.getId()),
						   RequestType::DELET);
}

//  :: Private slots ::

void TestEditingModel::jsonShortTestInfoReceived(const QJsonObject &jsonObject) const {
	ShortTestInfo shortTestInfo;
	shortTestInfo.initWithJsonObject(jsonObject);
	emit testNameAlreadyTaken(shortTestInfo);
}

void TestEditingModel::onTestDeleted(const Test &test) const {
	auto requester = makeRequesterWithDefaultErrorOutput();
	connect(requester, SIGNAL(success()),
			SIGNAL(testReplaced()));
	requester->sendRequest(PUT_TEST_API,
						   RequestType::PUT,
						   test.toJson());
}
