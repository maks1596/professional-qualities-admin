#pragma once

#include <QWidget>

class QAbstractItemModel;

namespace Ui {
class PersonalDataForm;
}

enum class Gender;

class PersonalDataForm : public QWidget {
    Q_OBJECT

public:
    explicit PersonalDataForm(QWidget *parent = nullptr);
    ~PersonalDataForm() override;

    QString getName() const;
    void setName(const QString &name);

    Gender getGender() const;
    void setGender(const Gender &gender);

    QDate getBirthdate() const;
    void setBirthdate(const QDate &birthdate);

    QString getProfession() const;
    void setProfession(const QString &profession);

    int getExpertAssessment() const;
    void setExpertAssessment(int expertAssessment);

    void setMaximumBirtdate(const QDate &maxDate);
    void setMinimumBirtdate(const QDate &minDate);

    void setMaximumExpertAssessment(int maxAssessment);
    void setMinimumExpertAssessment(int minAssessment);

    QStringList getProfessions() const;
    void setProfessions(const QStringList &professions);

    void setUserExcludedFromAsstimationMessageVisibility(bool visible);


signals:
    void nameChanged(const QString &name);
    void genderChanged(Gender gender);
    void birthdateChanged(const QDate &birthdate);
    void professionChanged(const QString &profession);
    void expertAssessmentChanged(int assessment);

private:
    void setMinimumExpertAssessmentToolTip(int assessment);

    Ui::PersonalDataForm *ui;
};
