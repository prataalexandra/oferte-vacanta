#include "custom_model.h"

QVariant CustomTableModel::data(const QModelIndex& index, int role) const {
	int row = index.row();
	int col = index.column();

	if (role == Qt::DisplayRole) {
		if (col == 0)
			return QString::fromStdString(product_list[row].getDenumire());
		else if (col == 1)
			return QString::fromStdString(product_list[row].getDestinatie());
	}
	return QVariant();
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const {

	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		switch (section) {
		case 0:
			return QString("Denumire");
		case 1:
			return QString("Destinatie");
		}
	}

	return QVariant();
}