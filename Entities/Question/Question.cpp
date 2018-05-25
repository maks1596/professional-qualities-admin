#include "Question.h"

#include <QJsonArray>

//  :: Constants ::

const QString ID_JSON_KEY = "id";
const QString FORMULATION_JSON_KEY = "formulation";
const QString ANSWER_OPTIONS_JSON_KEY = "answerOptions";

//  :: Implementation ::

struct Question::Implementation {
	int id = 0;
	QString formulation;
	AnswerOptions answerOptions;
};

//  :: Lifecycle ::
//  :: Constructors ::
Question::Question() : pimpl(new Implementation()) {}

Question::Question(const QString &formulation) : Question() {
	setFormulation(formulation);
}

//  :: Copy ::
Question::Question(const Question &other)
	: pimpl(new Implementation(*other.pimpl))
{ }
Question &Question::operator=(const Question &other) {
	*pimpl = *other.pimpl;
	return *this;
}

//  :: Move ::
Question::Question(Question &&other) : pimpl(other.pimpl.take()) {}
Question &Question::operator=(Question &&other) {
	pimpl.swap(other.pimpl);
	return *this;
}

//  :: Destructor ::
Question::~Question() {}

//  :: Accessors ::
//  :: ID ::
int Question::getId() const {
	return pimpl->id;
}
void Question::setId(const int &id) {
	pimpl->id = id;
}

//  :: Formulation ::
QString Question::getFormulation() const {
	return pimpl->formulation;
}
void Question::setFormulation(const QString &formualtion) {
	pimpl->formulation = formualtion;
}

//  :: Answer options ::
AnswerOptions Question::getAnswerOptions() const {
	return pimpl->answerOptions;
}
AnswerOptions *Question::getAnswerOptions() {
	return &pimpl->answerOptions;
}
void Question::setAnswerOptions(const AnswerOptions &answerOptions) {
	pimpl->answerOptions = answerOptions;
}

//  :: Public methods ::

void Question::addAnswerOption(AnswerOption answerOption) {
	pimpl->answerOptions.append(answerOption);
}

//  :: Serializable ::

QJsonObject Question::toJson() const {
	QJsonObject json;

	json[ID_JSON_KEY] = getId();
	json[FORMULATION_JSON_KEY] = getFormulation();

    QJsonArray jsonAnswerOptions;
	for (const auto &answerOption : getAnswerOptions()) {
        jsonAnswerOptions.append(answerOption.toJson());
    }
	json[ANSWER_OPTIONS_JSON_KEY] = jsonAnswerOptions;

	return json;
}

void Question::initWithJsonObject(const QJsonObject &json) {
	if (json.contains(ID_JSON_KEY) && json[ID_JSON_KEY].isDouble()) {
		setId(json[ID_JSON_KEY].toInt());
    }
	if (json.contains(FORMULATION_JSON_KEY) &&
			json[FORMULATION_JSON_KEY].isString()) {
		setFormulation(json[FORMULATION_JSON_KEY].toString());
    }
	if (json.contains(ANSWER_OPTIONS_JSON_KEY) &&
			json[ANSWER_OPTIONS_JSON_KEY].isArray()) {
		QJsonArray jsonAnswerOptions = json[ANSWER_OPTIONS_JSON_KEY].toArray();
        AnswerOption answerOption;
		getAnswerOptions()->clear();

        for (const auto &jsonAnswerOption : jsonAnswerOptions) {
            if (jsonAnswerOption.isObject()) {
                answerOption.initWithJsonObject(jsonAnswerOption.toObject());
				getAnswerOptions()->append(answerOption);
            }
        }
    }
}
