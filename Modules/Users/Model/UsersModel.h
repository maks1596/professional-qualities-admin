#pragma once

#include <QAbstractTableModel>
#include <QList>

class User;

class UsersModel : public QAbstractTableModel {
public:
    UsersModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    const QList<User> &getUsers() const;
    void setUsers(const QList<User> &users);

    User getUser(uint index) const;
    int getUserId(uint index) const;
    int getRemoveColumnIndex() const;

private:
    QList<User> m_users;
};
