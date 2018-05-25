#pragma once

#include <QWidget>
#include <QString>

#include "Forms/EditFormulationForm/EditFormulationForm.h"

namespace Ui {
class FormulationForm;
}

class FormulationForm : public QWidget {
    Q_OBJECT

signals:
    void formulationChanged(const QString &newFormulation,
                            const QString &oldFormulation);
    void formulationDeleted(const QString &formulation);

public:
    explicit FormulationForm(const unsigned &number,
                             const QString &separator,
                             const QString &formulation,
                             QWidget *parent = nullptr);
    ~FormulationForm();

    unsigned getNumber() const;
    void setNumber(const unsigned &number);
    void decreaseNumber();
    void increaseNumber();

    QString getFormulation() const;
    void setFormulation(const QString &formulation);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    bool event(QEvent *event) override;

private slots:
    void onEditingFinished(const QString &newFormulation);
    void onFormulationDeleted();

private:
    void toEditForm();
    void toReadForm();

    void showEditForm();
    void hideEditForm();

    void showReadForm();
    void hideReadForm();

    unsigned m_number;
    QString m_separator;
    EditFormulationForm *m_editForm;
    Ui::FormulationForm *ui;
};
