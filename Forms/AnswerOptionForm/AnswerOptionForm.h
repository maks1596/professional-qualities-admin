#ifndef ANSWEROPTION_FORM_H
#define ANSWEROPTION_FORM_H

#include <QWidget>

class AnswerOption;
class FormulationForm;

class AnswerOptionForm : public QWidget {
Q_OBJECT

public:
    explicit AnswerOptionForm(const uint& number,
                              AnswerOption *answerOption,
                              QWidget *parent = nullptr);

signals:
    void answerOptionDeleted(const QString &formulation);

public slots:
    void decreaseNumber();

private slots:
    void onFormulationChanged(const QString &newFormulation);

private:
    AnswerOption *m_answerOption;
    FormulationForm *m_formulationForm;
};

#endif // ANSWEROPTION_FORM_H
