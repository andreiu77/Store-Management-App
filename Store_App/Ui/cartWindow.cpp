#include "cartWindow.h"

cartWindow::cartWindow(std::vector<TrenchCoat> list, QObject* parent) : QAbstractTableModel(parent), coats(list)
{
	headers << "Size" << "Colour" << "Price" << "Photograph";
}

int cartWindow::rowCount(const QModelIndex& parent) const
{
	return coats.size();
}

int cartWindow::columnCount(const QModelIndex& parent) const
{
	return headers.size();
}

QVariant cartWindow::data(const QModelIndex& index, int role) const
{
	if (!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	const TrenchCoat& coat = coats[index.row()];
	switch (index.column())
	{
		case 0:
			return QString::fromStdString(coat.getSize());
		case 1:
			return QString::fromStdString(coat.getColour());
		case 2:
			return QString::number(coat.getPrice());
		case 3:
			return QString::fromStdString(coat.getPhotograph());
		default:
			return QVariant();
	}
}

QVariant cartWindow::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal)
		return headers[section];
	else
		return QVariant();
}
