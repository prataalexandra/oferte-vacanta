#pragma once
#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <qmessagebox.h>
#include "Service.h"
#include "Service_cos.h"
#include <qdebug.h>
#include <vector>
#include <string>
#include "custom_model.h"
using namespace std;

class ProductGUI : public QWidget {
private:
    Agentie& serv;
    CosService& serv_cos;

    //QListWidget* list_layout = new QListWidget;
    QTableView* tabel = new QTableView;
    QTableWidget* lista_cos = new QTableWidget{ 10, 2 };
    QHBoxLayout* new_button_layout = new QHBoxLayout{};
    //QPushButton* butonExit = new QPushButton{ "&Exit" };
    QPushButton* butonAdd = new QPushButton{ "&Adauga" };
    QPushButton* butonModifica = new QPushButton{ "&Modifica" };
    QPushButton* butonSterge = new QPushButton{ "&Sterge" };
    QPushButton* butonUndo = new QPushButton{ "&Undo" };
    QPushButton* butonSortName = new QPushButton{ "&Sort Denumire" };
    QPushButton* butonSortTipPret = new QPushButton{ "&Sort TipPret" };
    QPushButton* butonSortDestinatie = new QPushButton{ "&Sort Destinatie" };
    QPushButton* butonFiltrarePretMin = new QPushButton{ "&PretMin" };
    QPushButton* butonRevenire = new QPushButton{ "&Revenire" };
    QPushButton* butonAdaugaCos = new QPushButton{ "&AdaugaCos" };
    QPushButton* butonCartCrud = new QPushButton{ "&Cos" };
    QPushButton* butonCartRead = new QPushButton{ "&Cos DESEN" };
    CustomTableModel* model = new CustomTableModel{ serv.get_all_service()};
    
    
    //QPushButton* butonStergeCos = new QPushButton{ "&StergeCos" };
    //QPushButton* butonGenerareCos = new QPushButton{ "&GenerareCos" };
    QPushButton* butonExport = new QPushButton{ "&Export" };
    //QPushButton* butonFiltrarePretMinMax = new QPushButton{ "&PretMinMax" };

    QLineEdit* text_denumire = new QLineEdit;
    QLineEdit* text_destinatie = new QLineEdit;
    QLineEdit* text_tip = new QLineEdit;
    QLineEdit* text_pret = new QLineEdit;
    QLineEdit* text_fisier = new QLineEdit;

    void create_interface();

    void load_data(const vector<Oferta>& lista);

    void load_data_cos(const vector<Oferta>& lista);

    void interface_connect();

    void GUIadd();

    void GUIadd_cos();

    void GUImodifica();

    void GUIundo();

    void GUIaddtype();

    void GUIsterge();

    void GUIopencartCrud();

    void GUIopencartRead();

public:
    ProductGUI(Agentie& serv, CosService& serv_cos) : serv{ serv }, serv_cos{ serv_cos }
    {
        create_interface();
        serv.populate();
        load_data(serv.get_all_service());
        interface_connect();
    }
    /*ProductGUI(Agentie& serv, CosService& serv_cos) : serv{serv}, serv_cos{serv_cos} {}
    {
        create_interface();
        serv.populate();
        load_data(serv.get_all_service());
        interface_connect();
    }*/

};

