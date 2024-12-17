#include <QAbstractTableModel>
#include <Domain/Domain.h>
#pragma once
class cartWindow : public QAbstractTableModel
{
	Q_OBJECT;

private:
	QStringList headers;
	std::vector<TrenchCoat> coats;
public:
	explicit cartWindow(std::vector<TrenchCoat> list, QObject *parent = nullptr);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

