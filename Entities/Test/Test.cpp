#include "Test.h"

#include "QJsonArray"

#include "Entities/EvaluationMap/EvaluationMap.h"
#include "Exception.h"
#include "Entities/Key/Key.h"
#include "Entities/Key/GeneralAnswerOptions/GeneralAnswerOptionsKey.h"
#include "Entities/Key/UniqueAnswerOptions/UniqueAnswerOptionsKey.h"

#include "JsonArraySerialization.h"

//  :: Constants ::

const QString RUS_ALPHABETIC = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
const QString ENG_ALPHABETIC = "abcdefghijklmnopqrstuvwxyz";

const QString ID_JSON_KEY = "id";
const QString NAME_JSON_KEY = "name";
const QString INSTRUCTION_JSON_KEY = "instruction";
const QString QUESTIONS_JSON_KEY = "questions";
const QString GENERAL_ANSWER_OPTIONS_JSON_KEY = "generalAnswerOptions";
const QString SCALES_JSON_KEY = "scales";

//  :: Private function headers ::

uint answerOptionToIndex(const AnswerOption &source,
						 int amountOfAnswerOptions);

//  :: Serialization functions ::
AnswerOptions answerOptionsFromJsonArray(const QJsonArray &jsonArray);
Questions questionsFromJsonArray(const QJsonArray &jsonArray);
Scales scalesFromJsonArray(const QJsonArray &jsonArray);

//  :: Implementation ::

struct Test::Implementation {
	QString instruction;
	AnswerOptionsType answerOptionsType = UNDEFINED;
	AnswerOptions generalAnswerOptions;
	Questions questions;
	Scales scales;

	int curScaleIndex;
};

//  :: Lifecycle ::
//  :: Constructors ::
Test::Test(int id/*= 0*/,
		   const QString &name/*= ""*/)
	: ShortTestInfo(id, name),
	  pimpl(new Implementation()) {
	setName(name);
}

//  :: Copy ::
Test::Test(const Test &other)
	: ShortTestInfo(other),
	  pimpl(new Implementation(*other.pimpl))
{ }
Test &Test::operator=(const Test &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
Test::Test(Test &&other)
	: ShortTestInfo(other),
	  pimpl(other.pimpl.take())
{ }
Test &Test::operator=(Test &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
Test::~Test() {}

//  :: Public accessors ::
//  :: Instruction ::
QString Test::getInstruction() const {
	return pimpl->instruction;
}
void Test::setInstruction(const QString &instruction) {
	pimpl->instruction = instruction;
}

//  :: Questions ::
const Questions &Test::getQuestions() const {
	return pimpl->questions;
}
Questions *Test::getQuestions() {
	return &pimpl->questions;
}
void Test::setQuestions(const Questions &questions) {
	pimpl->questions = questions;
}

//  :: Answer options type ::
AnswerOptionsType Test::getAnswerOptionsType() const {
	return pimpl->answerOptionsType;
}
void Test::setAnswerOptionsType(const AnswerOptionsType &type) {
    if(type != UNDEFINED) {
		pimpl->answerOptionsType = type;
    } else {
        throw SettingUndefinedAnswerOptionsType();
    }
}

//  :: General answer options ::
AnswerOptions Test::getGeneralAnswerOptions() const {
	return pimpl->generalAnswerOptions;
}
AnswerOptions* Test::getGeneralAnswerOptions() {
	return &pimpl->generalAnswerOptions;
}
void Test::setGeneralAnswerOptions(const AnswerOptions &answerOptions) {
	pimpl->generalAnswerOptions = answerOptions;
}

//  :: Scales ::
Scales *Test::getScales() {
	return &pimpl->scales;
}
const Scales &Test::getScales() const {
	return pimpl->scales;
}
void Test::setScales(const Scales &scales) {
	pimpl->scales = scales;
}

//  :: Public methods ::

void Test::addQuestion(const Question &question) {
	getQuestions()->append(question);
}

//  :: Unique answer options ::
void Test::addAnswerOptionToLastQuestion(const AnswerOption &answerOption) {
	switch(getAnswerOptionsType()) {
	case UNDEFINED: {
		setAnswerOptionsType(UNIQUE);
	}

	case UNIQUE: {
		if(answerOption.getFormulation().isEmpty()) {
			return;
		}
		getQuestions()->back().addAnswerOption(answerOption);
	} break;

	case GENERAL: {
		throw SettingUniqueAnswerOptionForQuestionsWithGeneralAnswerOptions();
	} break;
	}
}

//  :: General answer options ::
void Test::addGeneralAnswerOption(const AnswerOption &answerOption) {
	switch(getAnswerOptionsType()) {
	case UNDEFINED: {
		setAnswerOptionsType( GENERAL);
	}
	case GENERAL: {
		if(answerOption.getFormulation().isEmpty()) {
			return;
		}
		getGeneralAnswerOptions()->append(answerOption);
	} break;
	case UNIQUE: {
		throw SettingGeneralAnswerOptionForQuestionsWithUniqueAnswerOptions();
	} break;
	}

}

//  :: Scales ::
void Test::toScale(const Scale &scale) {
	setCurrentScaleIndex(getScales()->indexOf(scale));
	if(getCurrentScaleIndex() < 0) {
		getScales()->append(scale);
		setCurrentScaleIndex(getScales()->size() - 1);
	}
}

bool Test::hasOnlyOneScale() const {
	return (getScales().size() == 1);
}

//  :: Key ::
void Test::addAnswerOptionToCurrentScale(const AnswerOption &answerOption) {
	if(answerOption.getFormulation().isEmpty()) {
		return;
	}

	switch(getAnswerOptionsType()) {
	case UNIQUE: {
		uint curQuestionIndex = getCurrentScale().getUniqueAnswerOptionsKey()
								->getCurrentQuestionIndex();
		Question question = getQuestions()->at(curQuestionIndex);
		addAnswerOptionFromContainer(answerOption, *question.getAnswerOptions());
	} break;

	case GENERAL: {
		addAnswerOptionFromContainer(answerOption, *getGeneralAnswerOptions());
	} break;

	case UNDEFINED: break;
	}
}

void Test::addQuestionToCurrentScale(const uint &questionNumber) {
	uint questionIndex = questionNumber - 1;
	if(questionIndex < (uint)getQuestions()->size()) {
		switch(getAnswerOptionsType()) {
		case GENERAL: {
			 getCurrentScale().getGeneralAnswerOptionsKey()
					->addQuestionToLastAnswerOption(questionIndex);
		} break;
		case UNIQUE: {
			 getCurrentScale().getUniqueAnswerOptionsKey()
					->addQuestion(questionIndex);
		} break;
		case UNDEFINED: break;
		}
	} else {
		throw QuestionNumberOutOfRange(questionNumber);
	}
}

void Test::setPointsToCurrentScale(const int &points) {
	getCurrentScale().getKey()->setPoints(points);
}

//  :: Evaluation map ::
void Test::addRangeToCurrentScale(const uint &lower/*, upper = lower*/) {
	addRangeToCurrentScale(lower, lower);
}
void Test::addRangeToCurrentScale(const uint &lower, const uint &upper) {
	 getCurrentScale().getEvaluationMap()->addAppraisedRange({lower, upper});
}

void Test::setResultToCurrentScale(const QString &result) {
	 getCurrentScale().getEvaluationMap()->setResultToLastRange(result);
}


//  :: Serializable ::

QJsonObject Test::toJson() const {
	QJsonObject json;

	json[ID_JSON_KEY] = getId();
	json[NAME_JSON_KEY] = getName();
	json[INSTRUCTION_JSON_KEY] = getInstruction();
    json[GENERAL_ANSWER_OPTIONS_JSON_KEY] =
            jsonArrayFromSerializableObjects(getGeneralAnswerOptions());
    json[QUESTIONS_JSON_KEY] = jsonArrayFromSerializableObjects(getQuestions());
    json[SCALES_JSON_KEY] = jsonArrayFromSerializableObjects(getScales());

	return json;
}

void Test::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(ID_JSON_KEY) && json[ID_JSON_KEY].isDouble()) {
		setId(json[ID_JSON_KEY].toInt());
	}
	if (json.contains(NAME_JSON_KEY) && json[NAME_JSON_KEY].isString()) {
		setName(json[NAME_JSON_KEY].toString());
	}
	if (json.contains(INSTRUCTION_JSON_KEY) &&
			json[INSTRUCTION_JSON_KEY].isString()) {
		setInstruction(json[INSTRUCTION_JSON_KEY].toString());
    }
	if (json.contains(GENERAL_ANSWER_OPTIONS_JSON_KEY) &&
			json[GENERAL_ANSWER_OPTIONS_JSON_KEY].isArray()) {
		auto jsonArray = json[GENERAL_ANSWER_OPTIONS_JSON_KEY].toArray();
		setGeneralAnswerOptions(answerOptionsFromJsonArray(jsonArray));
		setAnswerOptionsType(getGeneralAnswerOptions()->isEmpty() ?
								 UNIQUE : GENERAL);
    }
	if (json.contains(QUESTIONS_JSON_KEY) && json[QUESTIONS_JSON_KEY].isArray()) {
		auto jsonArray = json[QUESTIONS_JSON_KEY].toArray();
		setQuestions(questionsFromJsonArray(jsonArray));
    }
	if (json.contains(SCALES_JSON_KEY) && json[SCALES_JSON_KEY].isArray()) {
		setScales(scalesFromJsonArray(json[SCALES_JSON_KEY].toArray()));
	}
}

//  :: Private accessors ::

int Test::getCurrentScaleIndex() const {
	return pimpl->curScaleIndex;
}
void Test::setCurrentScaleIndex(int index) {
	pimpl->curScaleIndex = index;
}

//  :: Private methods ::

void Test::addAnswerOptionFromContainer(const AnswerOption &answerOption,
										const AnswerOptions &container) {
	int answerOptionIndex = container.indexOf(answerOption);
    if (answerOptionIndex < 0) {
		answerOptionIndex = answerOptionToIndex(answerOption,
												container.size());
    }

	switch(getAnswerOptionsType()) {
    case UNIQUE: {
		 getCurrentScale().getUniqueAnswerOptionsKey()
				->addAnswerOptionToLastQuestion(answerOptionIndex);
    } break;

    case GENERAL: {
		 getCurrentScale().getGeneralAnswerOptionsKey()
				->addAnswerOption(answerOptionIndex);
    } break;

    case UNDEFINED: break;
	}
}

Scale &Test::getCurrentScale() {
	return pimpl->scales[getCurrentScaleIndex()];
}
const Scale &Test::getCurrentScale() const {
	return pimpl->scales[getCurrentScaleIndex()];
}

//  :: Private functions ::

uint answerOptionToIndex(const AnswerOption &source,
						 int amountOfAnswerOptions) {
	auto formulation = source.getFormulation();
	bool ok;    // Возможно в строке номер ответа
	int index = formulation.toUInt(&ok) - 1;
	if (!ok && formulation.size() == 1) {
		// Может там буква ответа. а, б или в, например
		index = RUS_ALPHABETIC.indexOf(formulation[0].toLower());
		if(index < 0) {
			// Может английская буква
			index = ENG_ALPHABETIC.indexOf(formulation[0].toLower());
			if(index < 0) {
				throw InvalidAnswerOption(source);
			}
		}
	}

	if (0 <= index && index < amountOfAnswerOptions) {
		return index;
	} else {
		throw InvalidAnswerOption(source);
	}
}

//  :: Serialization ::

AnswerOptions answerOptionsFromJsonArray(const QJsonArray &jsonArray) {
    return serializableObjectsFromJsonArray<QList, AnswerOption>(jsonArray);
}

Questions questionsFromJsonArray(const QJsonArray &jsonArray) {
    return serializableObjectsFromJsonArray<QList, Question>(jsonArray);
}

Scales scalesFromJsonArray(const QJsonArray &jsonArray) {
    return serializableObjectsFromJsonArray<QList, Scale>(jsonArray);
}
