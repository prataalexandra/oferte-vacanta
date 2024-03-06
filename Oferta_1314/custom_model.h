#pragma once
#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "Oferta.h"
using namespace std;

class CustomTableModel : public QAbstractTableModel {
private:
	vector <Oferta> product_list;

public:

	CustomTableModel(const vector<Oferta>& product_list) : product_list{ product_list } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return int(product_list.size());
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 2;
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void setProduct(const vector<Oferta>& new_list) {


		product_list = new_list;
		auto topLeft = createIndex(0, 0);
		auto bottomRight = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(topLeft, bottomRight);
	}
};

