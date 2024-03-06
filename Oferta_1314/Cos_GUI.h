#pragma once
#pragma once
#include <QWidget.h>
#include "Service_cos.h"
#include <QListWidget.h>
#include <QLayout.h>
#include <QtWidgets/qpushbutton.h>
#include "Service.h"

class CosGUI : public QWidget {
private:
	CosService& srv;
	void initGUIcmps();
	void connectSignalsSlots();
	void reloadList(const vector<Oferta>& prod);

	QHBoxLayout* mainLayout = new QHBoxLayout;
	QListWidget* prodWidget = new QListWidget;
	QPushButton* btngolireCos = new QPushButton("Golire cos");


public:
	CosGUI(CosService& srv) : srv{ srv }
	{
		initGUIcmps();
		connectSignalsSlots();
		reloadList(srv.cos_get_all_service());
	}
	void golire();
};
