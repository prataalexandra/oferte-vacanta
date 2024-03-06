#include "GUI.h"
#include "Cos_GUI.h"
#include <QtWidgets/QHBoxLayout>
#include "cos_read_gui.h"
#include "cos_crud_gui.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QRadioButton>
#include <qpalette.h>
#include <qbrush.h>
#include<qdebug.h>
#include <qdialog.h>
#include <string>
#include <algorithm>
#include "Cos_GUI.h"

void ProductGUI::create_interface()
{
    QHBoxLayout* main_layout = new QHBoxLayout{};
    setLayout(main_layout);

    auto left_part = new QVBoxLayout;
    //left_part->addWidget(list_layout);
    tabel->setModel(model);
    left_part->addWidget(tabel);
    left_part->addWidget(butonSortName);
    left_part->addWidget(butonSortDestinatie);
    left_part->addWidget(butonSortTipPret);
    left_part->addWidget(butonFiltrarePretMin);
    main_layout->addLayout(left_part);

    auto middle_part = new QVBoxLayout;
    //middle_part->addWidget(lista_cos);

    auto form_layout = new QFormLayout;
    form_layout->addRow("Denumire", text_denumire);
    form_layout->addRow("Destinatie", text_destinatie);
    form_layout->addRow("Tip", text_tip);
    form_layout->addRow("Pret", text_pret);
    form_layout->addRow("Nume fisier", text_fisier);
    middle_part->addLayout(form_layout);

    auto butoane_cos = new QHBoxLayout{};
    butoane_cos->addWidget(butonAdaugaCos);
    butoane_cos->addWidget(butonCartCrud);
    butoane_cos->addWidget(butonCartRead);

    auto button_layout = new QHBoxLayout{};
    button_layout->addWidget(butonAdd);
    button_layout->addWidget(butonSterge);
    button_layout->addWidget(butonModifica);
    button_layout->addWidget(butonUndo);
    button_layout->addWidget(butonRevenire);
    button_layout->addWidget(butonExport);
    middle_part->addLayout(button_layout);

    main_layout->addLayout(middle_part);
    main_layout->addLayout(butoane_cos);
    main_layout->addLayout(new_button_layout);
}

void ProductGUI::interface_connect()
{
    QObject::connect(butonSortName, &QPushButton::clicked, [&]() { load_data(serv.sortDenumire()); });

    QObject::connect(butonFiltrarePretMin, &QPushButton::clicked, [&]() {
        auto pret = text_pret->text();
        int valoare_pret = 0;
        valoare_pret = stof(pret.toStdString());
        load_data(serv.filtrarePretMaiMic(valoare_pret));
        });

    QObject::connect(butonSortTipPret, &QPushButton::clicked, [&]() { load_data(serv.sortTipPret()); });

    QObject::connect(butonSortDestinatie, &QPushButton::clicked, [&]() { load_data(serv.sortDestinatie()); });

    QObject::connect(butonRevenire, &QPushButton::clicked, [&]() { load_data(serv.getAll()); });

    QObject::connect(butonCartCrud, &QPushButton::clicked, [&]() { GUIopencartCrud(); });

    QObject::connect(butonCartRead, &QPushButton::clicked, [&]() { GUIopencartRead(); });

    //QObject::connect(butonExit, &QPushButton::clicked, [&]() { close(); });

    QObject::connect(butonAdd, &QPushButton::clicked, [&]() { GUIadd(); });

    QObject::connect(butonAdaugaCos, &QPushButton::clicked, [&]()
        {
            try {
                Oferta p = serv.search_service(text_denumire->text().toStdString(), text_destinatie->text().toStdString());
                serv_cos.cos_add_service(p.getDenumire(), p.getDestinatie());
                serv_cos.notify();

            }
            catch (OfertaException& ex)
            {
                //QMessageBox::warning(this, "Avertizare", QString::fromStdString(ex.getMsg()));
            }
        });

    /*QObject::connect(butonStergeCos, &QPushButton::clicked, [&]() {
        serv_cos.cos_delete_service();
        lista_cos->clear(); });

    QObject::connect(butonGenerareCos, &QPushButton::clicked, [&]() {
        lista_cos->clear();
        serv_cos.cos_generate_service();
        load_data_cos(serv_cos.cos_get_all_service());
        });
    */

    //QObject::connect(list_layout, &QListWidget::itemSelectionChanged, [&]() { GUIselect(); });

    QObject::connect(butonExport, &QPushButton::clicked, [&]() {
        auto nume_fisier = text_fisier->text();
        string fisier = nume_fisier.toStdString();
        serv_cos.exportToFile(fisier);
        });

    QObject::connect(butonModifica, &QPushButton::clicked, [&]() { GUImodifica(); });

    QObject::connect(butonUndo, &QPushButton::clicked, [&]() { GUIundo(); });

    QObject::connect(butonSterge, &QPushButton::clicked, [&]() { GUIsterge(); });

    QObject::connect(tabel->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
        if (tabel->selectionModel()->selectedIndexes().isEmpty()) {
            text_denumire->setText("");
            text_destinatie->setText("");
            text_tip->setText("");
            text_pret->setText("");
            return;
        }

        int selected_row = tabel->selectionModel()->selectedIndexes().at(0).row();
        auto first_cel = tabel->model()->index(selected_row, 0);
        auto second_cel = tabel->model()->index(selected_row, 1);

        auto name = tabel->model()->data(first_cel, Qt::DisplayRole).toString();
        auto producer = tabel->model()->data(second_cel, Qt::DisplayRole).toString();

        text_denumire->setText(name);
        text_destinatie->setText(producer);
        auto produs = serv.search_service(name.toStdString(), producer.toStdString());
        text_pret->setText(QString::number(produs.getPret()));
        text_tip->setText(QString::fromStdString(produs.getTip()));
        });
}

void ProductGUI::load_data(const vector<Oferta>& lista)
{
    model->setProduct(lista);
    /*list_layout->clear();;
    for (const auto& oferta : lista)
    {
        QListWidgetItem* item = new QListWidgetItem();
        item->setText(QString::fromStdString(oferta.getDenumire()));
        item->setData(Qt::UserRole, QString::fromStdString(oferta.getDestinatie()));
        list_layout->addItem(item);
    }*/
}

void ProductGUI::load_data_cos(const vector<Oferta>& lista)
{

    lista_cos->clearContents();
    lista_cos->setRowCount(lista.size());

    for (int i = 0; i < lista.size(); ++i)
    {
        const Oferta& oferta = lista[i];

        QTableWidgetItem* denumireItem = new QTableWidgetItem(QString::fromStdString(oferta.getDenumire()));
        QTableWidgetItem* destinatieItem = new QTableWidgetItem(QString::fromStdString(oferta.getDestinatie()));

        lista_cos->setItem(i, 0, denumireItem);
        lista_cos->setItem(i, 1, destinatieItem);
    }

}

void ProductGUI::GUIadd()
{
    auto denumire = text_denumire->text();
    auto destinatie = text_destinatie->text();
    auto tip = text_tip->text();
    auto pret = text_pret->text();
    int valoare_pret = 0;
    try {
        valoare_pret = stof(pret.toStdString());
        try {
            serv.addOferta(denumire.toStdString(), destinatie.toStdString(), tip.toStdString(), valoare_pret);
            GUIaddtype();
            load_data(serv.get_all_service());
        }
        catch (OfertaException)
        {
            QMessageBox::information(nullptr, "Eroare!", "Oferta exista deja!");
        }
        catch (ValidateException)
        {
            QMessageBox::information(nullptr, "Eroare!", "Oferta invalida!");
        }
    }
    catch (std::invalid_argument)
    {
        QMessageBox::information(nullptr, "Eroare!", "Oferta invalida!");
    }
    text_denumire->clear();
    text_destinatie->clear();
    text_tip->clear();
    text_pret->clear();
}


/*void ProductGUI::GUIadd_cos()
{
    if (list_layout->currentItem() != nullptr)
    {
        auto index = list_layout->currentIndex().row();
        auto denumire = serv.getAll()[index].getDenumire();
        auto destinatie = serv.getAll()[index].getDestinatie();
        serv_cos.cos_add_service(denumire, destinatie);
        load_data_cos(serv_cos.cos_get_all_service());
    }
}*/


void ProductGUI::GUIsterge()
{
    auto denumire = text_denumire->text();
    auto destinatie = text_destinatie->text();
    //auto tip = text_tip->text();
    //auto pret = text_pret->text();
    //float valoare_pret = 0;
    //valoare_pret = stof(pret.toStdString());
    try {
        serv.stergeOferta(denumire.toStdString(), destinatie.toStdString());
        load_data(serv.get_all_service());
        GUIaddtype();
    }
    catch (OfertaException)
    {
        QMessageBox::information(nullptr, "Eroare!", "Produsul nu exista!");
    }
    catch (std::invalid_argument)
    {
        QMessageBox::information(nullptr, "Eroare!", "Pret invalid!");
    }
}




void ProductGUI::GUImodifica()
{
    auto denumire = text_denumire->text();
    auto destinatie = text_destinatie->text();
    auto tip = text_tip->text();
    auto pret = text_pret->text();
    float valoare_pret = 0;
    try {
        valoare_pret = stof(pret.toStdString());
        try {
            serv.modificaOferta(denumire.toStdString(), destinatie.toStdString(), valoare_pret);
            load_data(serv.get_all_service());
            GUIaddtype();
        }
        catch (OfertaException)
        {
            QMessageBox::information(nullptr, "Eroare!", "Oferta nu exista!");
        }
    }
    catch (std::invalid_argument)
    {
        QMessageBox::information(nullptr, "Eroare!", "Pret invalid!");
    }
}

void ProductGUI::GUIundo()
{
    try
    {
        serv.undo();
        GUIaddtype();
        load_data(serv.get_all_service());
    }
    catch (OfertaException)
    {
        QMessageBox::information(nullptr, "Eroare!", "Nu mai exista undo!");
    }
}

void ProductGUI::GUIaddtype()
{
    vector<Oferta> oferta_list = serv.get_all_service();
    vector<std::pair<string, int>> tipuri;
    for (auto oferta : oferta_list) {
        bool ok = false;
        int i = 0;
        for (auto type : tipuri) {
            if (type.first == oferta.getTip()) {
                ok = true;
                break;
            }
        }
        if (ok == true)
            tipuri[i].second++;
        else tipuri.emplace_back(oferta.getTip(), 1);
    }
    QLayoutItem* item;
    while ((item = new_button_layout->takeAt(0)) != NULL)
    {
        delete item->widget();
        delete item;
    }

    for (auto t : tipuri) {
        string tip = t.first;
        int nr = t.second;
        auto item = new QRadioButton(QString::fromStdString(tip));

        QObject::connect(item, &QRadioButton::clicked, [nr] {
            string n = std::to_string(nr);
            auto* lbl = new QLabel(QString::fromStdString(n));
            lbl->show();
            });
        new_button_layout->addWidget(item);
    }

}

void ProductGUI::GUIopencartCrud()
{
    auto* newWindow = new CartCRUDGUI{ serv,serv_cos };
    newWindow->run();
}
void ProductGUI::GUIopencartRead()
{

    auto* newWindow = new CartCRUDRead{ serv_cos };
    newWindow->show();
}