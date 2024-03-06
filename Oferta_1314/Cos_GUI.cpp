#include "Cos_GUI.h"
#include <qtimer.h>

void CosGUI::initGUIcmps()
{
	setLayout(mainLayout);
	mainLayout->addWidget(prodWidget);
	mainLayout->addWidget(btngolireCos);
}

void CosGUI::connectSignalsSlots()
{
	QObject::connect(btngolireCos, &QPushButton::clicked, this, &CosGUI::golire);
	QTimer* refreshTimer = new QTimer;
	QObject::connect(refreshTimer, &QTimer::timeout, [this]() {
		reloadList(srv.cos_get_all_service());
		});

	refreshTimer->start(1000);


}
void CosGUI::golire()
{
	srv.cos_delete_service();
	reloadList(srv.cos_get_all_service());
}
void CosGUI::reloadList(const vector<Oferta>& prod)
{
	prodWidget->clear();
	for (const auto& p : prod)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.getDenumire()));
		item->setData(Qt::UserRole, QString::fromStdString(p.getTip()));
		if (p.getPret() > 100)
		{
			item->setData(Qt::BackgroundRole, QBrush{ Qt::red, Qt::SolidPattern });
		}
		prodWidget->addItem(item);

	}
}