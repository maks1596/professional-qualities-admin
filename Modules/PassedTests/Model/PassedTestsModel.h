#pragma once

#include <QAbstractTableModel>

#include "Entities/PassedTestPreview/PassedTestPreview.h"

class QTimer;
class PassedTestPreview;
class PassedTestsService;

class PassedTestsModel : public QAbstractTableModel {
    Q_OBJECT

public:
    //  :: Lifecycle ::
    PassedTestsModel(QObject *parent = nullptr);

    //  :: QAbstractTableModel ::

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    //  :: Accessors ::
    QList<PassedTestPreview> getPassedTestPreviews() const;
    void setPassedTestPreviews(const QList<PassedTestPreview> &previews);

    /**
     * @brief Возвращает ID пройденного теста, соответствующего переданному индексу
     * @param index - индекс модели
     * @return ID пройденного теста
     */
    int getId(const QModelIndex &index) const;

public slots:
    void startUpdating() const;
    void stopUpdating() const;

private:
    void initService();
    void initTimer();
    void checkRowsCountChanged(const QList<PassedTestPreview> &newPreviews);
    void emitAllDataChanged();

    QList<PassedTestPreview> m_previews;
    QTimer *m_timer;
    PassedTestsService *m_service;
};
