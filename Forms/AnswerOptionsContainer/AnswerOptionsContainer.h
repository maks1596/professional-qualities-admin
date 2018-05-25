#pragma once

#include <QWidget>
#include <QEvent>
#include <QList>

#include "Entities/AnswerOption/AnswerOption.h"
#include "Forms/AnswerOptionForm/AnswerOptionForm.h"

namespace Ui {
class AnswerOptionsContainer;
}

class AnswerOptionsContainer : public QWidget {
    Q_OBJECT

public:
    explicit AnswerOptionsContainer(AnswerOptions *answerOptions,
                                    bool hideAddForm,
                                    QWidget *parent = nullptr);
    ~AnswerOptionsContainer();

    AnswerOptions *getAnswerOptions();
    AnswerOptions copyAnswerOptions();
    void addAnswerOption(const AnswerOption &answerOption);
    void setAnswerOptions(AnswerOptions *answerOptions);


    void clear();

protected:
    bool event(QEvent *event) override;

private slots:
    void onAnswerOptionDeleted(const QString &formulation);
    void onAddAnswerOptionBtnClicked();

private:
    void addAnswerOptionForm(const uint &number,
                             AnswerOption *answerOption);
    void connectNewAnswerOptionToOld(AnswerOptionForm *newAnswerOption);
    void setAddFormHidden(bool hidden);
    void deleteAnswerOptionForms();

    AnswerOptions *m_answerOptions;
    bool m_hideAddForm;
    Ui::AnswerOptionsContainer *ui;
};
