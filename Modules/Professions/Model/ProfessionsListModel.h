#pragma once

#include <QAbstractListModel>

class QTimer;
class ProfessionsService;

class ProfessionsListModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit ProfessionsListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    ProfessionsService *getService() const;
    void setService(ProfessionsService *service);

    const QStringList &getProfessions() const;

    void startUpdating();
    void stopUpdating();

private:
    void initTimer();
    void checkProfessionsCountChanged(const QStringList &newProfessions);
    void emitAllDataChanged();

    void setProfessions(const QStringList &professions);

    ProfessionsService *m_service = nullptr;
    QTimer *m_timer;
    QStringList m_professions;
};
