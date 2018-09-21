#pragma once

#include <QObject>

class EditUserView;
class EditUserService;
class User;

class EditUserController : public QObject {
    Q_OBJECT
public:
    EditUserController(QObject *parent = nullptr);

    //  :: Accessors ::

    EditUserView *getView() const;
    void setView(EditUserView *view);

    EditUserService *getService() const;
    void setService(EditUserService *service);

private slots:
    void saveChanges() const;

private:
    EditUserView *m_view;
    EditUserService *m_service;
};
