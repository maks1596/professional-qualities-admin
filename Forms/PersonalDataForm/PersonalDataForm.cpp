#include "PersonalDataForm.h"
#include "ui_PersonalDataForm.h"

#include "Entities/Gender/Gender.h"

//  :: Constatnts ::

const QString MINIMUM_EXPERT_ASSESSMENT_HINT_FORMAT =
        "При значении %1 данные пользователя не будут использоваться в оценивании";

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
    connect(ui->professionComboBox, &QComboBox::currentTextChanged,
            this, &PersonalDataForm::professionChanged);
    connect(ui->assessmentSpinBox, SIGNAL(valueChanged(int)),
            SIGNAL(expertAssessmentChanged(int)));

    setMinimumExpertAssessmentToolTip(ui->assessmentSpinBox->minimum());
    setUserExcludedFromAsstimationMessageVisibility(false);
}

PersonalDataForm::~PersonalDataForm() {
    delete ui;
}

//  :: Public accessors ::
//  :: Name ::
QString PersonalDataForm::getName() const {
    return ui->nameLineEdit->text();
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

//  :: Public methods ::

//  :: Birtdate range ::
void PersonalDataForm::setMaximumBirtdate(const QDate &maxDate) {
    ui->birthdateEdit->setMaximumDate(maxDate);
}
void PersonalDataForm::setMinimumBirtdate(const QDate &minDate) {
    ui->birthdateEdit->setMinimumDate(minDate);
}

//  :: Expert assessment range ::
void PersonalDataForm::setMaximumExpertAssessment(int maxAssessment) {
    ui->assessmentSpinBox->setMaximum(maxAssessment);
}
void PersonalDataForm::setMinimumExpertAssessment(int minAssessment) {
    ui->assessmentSpinBox->setMinimum(minAssessment);
    setMinimumExpertAssessmentToolTip(minAssessment);
}

//  :: Professions model ::
QAbstractItemModel *PersonalDataForm::getProfessionsModel() const {
    return ui->professionComboBox->model();
}
void PersonalDataForm::setProfessionsModel(QAbstractItemModel *model) {
    ui->professionComboBox->setModel(model);
}

//  :: Public methods ::

void PersonalDataForm::setUserExcludedFromAsstimationMessageVisibility(bool visible) {
    ui->userExcludedFromAsstimatoionLabel->setVisible(visible);
}

//  :: Private methods ::

inline
void PersonalDataForm::setMinimumExpertAssessmentToolTip(int assessment) {
    ui->assessmentSpinBox
            ->setToolTip(MINIMUM_EXPERT_ASSESSMENT_HINT_FORMAT
                         .arg(assessment));
}
