#ifndef EDITUSERDATAFORM_H
#define EDITUSERDATAFORM_H

#include <QWidget>

namespace Ui {
class EditUserDataForm;
}

class EditUserDataForm : public QWidget
{
    Q_OBJECT

public:
    explicit EditUserDataForm(QWidget *parent = nullptr);
    ~EditUserDataForm();

private:
    Ui::EditUserDataForm *ui;
};

#endif // EDITUSERDATAFORM_H
