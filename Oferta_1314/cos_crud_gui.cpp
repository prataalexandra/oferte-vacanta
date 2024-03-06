#include "cos_crud_gui.h"


void CartCRUDGUI::create_interface() {
    wnd->setLayout(layout);

    lista->setModel(model);
    layout->addWidget(lista);

    QVBoxLayout* btn = new QVBoxLayout{};
    btn->addWidget(butonCartDelete);
    btn->addWidget(butonCartGenerate);

    layout->addLayout(btn);
}

void CartCRUDGUI::load_data() {
    model->setProduct(cart_serv.cos_get_all_service());
}

void CartCRUDGUI::connect() {

    QObject::connect(butonCartDelete, &QPushButton::clicked, [&]() { GUIdeleteCart(); });

    QObject::connect(butonCartGenerate, &QPushButton::clicked, [&]() { GUIgenerateCart(); });

}

void CartCRUDGUI::update() {

    load_data();
}

void CartCRUDGUI::run() {
    this->cart_serv.addObserver(this);

    create_interface();
    connect();
    update();
    wnd->show();
}

void CartCRUDGUI::GUIdeleteCart()
{
    cart_serv.cos_delete_service();
    cart_serv.notify();
}

void CartCRUDGUI::GUIgenerateCart()
{
    try
    {
        cart_serv.cos_generate_service();
        cart_serv.notify();
    }
    catch (OfertaException)
    {
        QMessageBox::information(nullptr, "Eroare!", "Nu exista produse pe care sa le puteti genera!");
    }
}