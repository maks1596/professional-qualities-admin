#pragma once

#include <QWidget>
#include <QScopedPointer>

#include "Entities/Key/PartOfKey/PartOfKey.h"

class AddPartOfKeyForm : public QWidget {
Q_OBJECT

public:
    explicit AddPartOfKeyForm(QWidget *parent = nullptr);
	virtual ~AddPartOfKeyForm() noexcept = default;

	virtual void setPartOfKey(const PartOfKey &partOfKey) = 0;

signals:
	void editingFinished(const PartOfKey &partOfkey);

protected:
	QScopedPointer<PartOfKey> m_partOfKey;
};
