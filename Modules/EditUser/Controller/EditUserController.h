#pragma once

#include "../Output/EditUserOutput.h"

class EditUserView;
class EditUserService;
class User;

class EditUserController : public EditUserOutput {
    Q_OBJECT
public:
    EditUserController(const User &user, QObject *parent = nullptr);

    //  :: Accessors ::

    EditUserView *getView() const;
    void setView(EditUserView *view);

    EditUserService *getService() const;
    void setService(EditUserService *service);

private slots:
    void saveChanges() const;

private:
    int m_id = 0;
    EditUserView *m_view = nullptr;
    EditUserService *m_service = nullptr;
};
