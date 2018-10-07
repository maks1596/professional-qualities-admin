#pragma once

#include <QDate>
#include <QObject>
#include <QScopedPointer>

#include "Entities/Entity/Entity.h"

class QString;

enum class Gender;
enum class UserRole;

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
    User(User &&other) noexcept;
    User &operator=(User &&other) noexcept;

	//  :: Destructor ::
	virtual ~User() noexcept override;

	//  :: Accessors ::

    QString getLogin() const;
    void setLogin(const QString &login);

    QString getPassword() const;
    void setPassword(const QString &password);

    UserRole getRole() const;
    void setRole(UserRole role);

    QString getName() const;
    void setName(const QString &name);

	Gender getGender() const;
	void setGender(Gender gender);

	QString getGenderString() const;
	void setGenderString(const QString &genderString);

    QDate getBirthdate() const;
    void setBirthdate(const QDate &birthdate);
	uint getAge() const;


    QString getProfession() const;
    void setProfession(const QString &profession);

    int getExpertAssessment() const;
public slots:
	void setExpertAssessment(int expertAssessment);

public:
    class Builder {
    #define PROCESS(name, Name, type, parameterType) \
        public: Builder& set##Name(parameterType name); \
        private: type m_##name;

    #include "Builder/UserBuilderXMacros.h"

    #undef PROCESS

        public: User build() const;
    };

    //  :: Serializable ::
	virtual QJsonObject toJson() const override;
	virtual void initWithJsonObject(const QJsonObject &json) override;

private:
	struct Implementation;
	QScopedPointer<Implementation> pimpl;
};
