#include "PersonalDataForm.h"
#include "ui_PersonalDataForm.h"

#include "Entities/Gender/Gender.h"

//  :: Lifecycle ::

PersonalDataForm::PersonalDataForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonalDataForm)
{
    ui->setupUi(this);

    connect(ui->nameLineEdit, &QLineEdit::textChanged,
            this, &PersonalDataForm::nameChanged);

    connect(ui->maleRadioButton, &QRadioButton::clicked,
            [this](){ emit genderChanged(Gender::Male); });
    connect(ui->femaleRadioButton, &QRadioButton::clicked,
            [this](){ emit genderChanged(Gender::Female); });

    connect(ui->birthdateEdit, &QDateEdit::dateChanged,
            this, &PersonalDataForm::birthdateChanged);
    connect(ui->professionComboBox, &QComboBox::currentTextChanged(QString),
            this, &PersonalDataForm::professionChanged);
    connect(ui->assessmentSpinBox, &QSpinBox::valueChanged,
            this, &PersonalDataForm::expertAssessmentChanged);
}

PersonalDataForm::~PersonalDataForm() {
    delete ui;
}

//  :: Public accessors ::
//  :: Name ::
QString PersonalDataForm::getName() const {
    return ui->nameLineEdit;
}
void PersonalDataForm::setName(const QString &name) {
    ui->nameLineEdit->setText(name);
}

//  :: Gender ::
Gender PersonalDataForm::getGender() const {
    if (ui->maleRadioButton->isChecked()) {
        return Gender::Male;
    } else if (ui->femaleRadioButton->isChecked()) {
        return Gender::Female;
    } else {
        return Gender::None;
    }
}
void PersonalDataForm::setGender(const Gender &gender) {
    switch (gender) {
    case Gender::Male: {
        ui->maleRadioButton->click();
    } break;
    case Gender::Female: {
        ui->femaleRadioButton->click();
    } break;
    case Gender::None: {
        ui->maleRadioButton->setChecked(false);
        ui->femaleRadioButton->setChecked(false);
    } break;
    };
}

//  :: Birthdate ::
QDate PersonalDataForm::getBirthdate() const {
    return ui->birthdateEdit->date();
}
void PersonalDataForm::setBirthdate(const QDate &birthdate) {
    ui->birthdateEdit->setDate(birthdate);
}

//  :: Profession ::
QString PersonalDataForm::getProfession() const {
    return ui->professionComboBox->currentText();
}
void PersonalDataForm::setProfession(const QString &profession) {
    ui->professionComboBox->setCurrentText(profession);
}

//  :: Expert assessment ::
int PersonalDataForm::getExpertAssessment() const {
    return ui->assessmentSpinBox->value();
}
void PersonalDataForm::setExpertAssessment(int expertAssessment) {
    ui->assessmentSpinBox->setValue(expertAssessment);
}
