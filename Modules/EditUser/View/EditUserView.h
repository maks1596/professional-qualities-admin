#ifndef EDITUSERVIEW_H
#define EDITUSERVIEW_H

#include <QWidget>

namespace Ui {
class EditUserView;
}

class EditUserView : public QWidget
{
    Q_OBJECT

public:
    explicit EditUserView(QWidget *parent = nullptr);
    ~EditUserView();

private:
    Ui::EditUserView *ui;
};

#endif // EDITUSERVIEW_H
