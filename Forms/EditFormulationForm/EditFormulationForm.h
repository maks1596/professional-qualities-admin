#ifndef EDITANSWEROPTIONFORM_H
#define EDITANSWEROPTIONFORM_H

#include <QWidget>

namespace Ui {
class EditFormulationForm;
}

class EditFormulationForm : public QWidget {
    Q_OBJECT

signals:
    void editingFinished(const QString &newFormulation);

public:
    explicit EditFormulationForm(const QString &formulation, QWidget *parent = 0);
    ~EditFormulationForm();

private slots:
    void onEditingFinished();

private:
    Ui::EditFormulationForm *ui;
};

#endif // EDITANSWEROPTIONFORM_H
