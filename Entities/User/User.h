#pragma once

#include <QObject>
#include <QScopedPointer>

#include "Entities/Entity/Entity.h"
#include "Entities/Gender/Gender.h"

class QDate;
class QString;

class User : public QObject,
			 public Entity {
Q_OBJECT

public:
	//  :: Lifecycle ::
	//  :: Constructors ::
	User(int id = 0);

	//  :: Copy ::
	User(const User &other);
	User &operator=(const User &other);

	//  :: Move ::
	User(User &&other);
	User &operator=(User &&other);

	//  :: Destructor ::
	virtual ~User() noexcept override;

	//  :: Accessors ::

    QString getLogin() const;
    void setLogin(const QString &login);

    QString getPassword() const;
    void setPassword(const QString &password);

    QString getName() const;
    void setName(const QString &getName);

	Gender getGender() const;
	void setGender(Gender gender);

	QString getGenderString() const;
	void setGenderString(const QString &genderString);

	QDate getBirthday() const;
	void setBirthday(const QDate &birthday);
	uint getAge() const;


    QString getProfession() const;
    void setProfession(const QString &profession);

    int getExpertAssessment() const;
public slots:
	void setExpertAssessment(int expertAssessment);

public:
    //  :: Serializable ::
	virtual QJsonObject toJson() const override;
	virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
