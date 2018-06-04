#include "CorrelationsForm.h"

//  :: Lifecycle ::

CorrelationsForm::CorrelationsForm(QWidget *parent)
    : QTableView(parent) {}

//  :: Public methods ::

void CorrelationsForm::setModel(QAbstractItemModel *model) {
    QTableView::setModel(model);

    connect(model, &QAbstractItemModel::modelReset,
                         [this](){
            resizeColumnsToContents();
            resizeRowsToContents();
        });
}
