#include "GUI.h";
#include "Service.h"
#include "Service_cos.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	OfertaRepo rep;
	CosRepo cart_repo{ rep };
	Validator valid;
	CosService cart_serv{ cart_repo , valid };
	Agentie serv{ rep, valid };

	serv.get_all_service();

	ProductGUI interface { serv, cart_serv };
	interface.show();

	return a.exec();
}