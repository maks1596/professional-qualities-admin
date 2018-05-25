#ifndef TEST_MAIN_FORM_H
#define TEST_MAIN_FORM_H

#include <QWidget>

namespace Ui {
class TestMainForm;
}

class Test;

class TestMainForm : public QWidget{
Q_OBJECT

public:
    explicit TestMainForm(Test *test,
                          QWidget *parent = 0);
    ~TestMainForm();

    void setAnswerOptionsTypeEditable(bool editable);

private slots:
    void onAnswerOptionsTypeToggled(bool checked);
    void onNameEditingFinished();
    void onInstructionTextChanged();

private:
    void configureName();
    void configureInstruction();
    void configureAnswerOptionsType();
    void configureGeneralAnswerOptions();
    void configureQuestions();

    Test *m_test;
    Ui::TestMainForm *ui;
};

#endif // TEST_MAIN_FORM_H
