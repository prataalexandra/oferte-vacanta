#pragma once
#pragma once
#include "Repo.h"

class ActiuneUndo {
public:
    virtual void doUndo() = 0; // nu exista implementare, functie pur virtuala

    virtual ~ActiuneUndo() = default;

};

class UndoAdauga : public ActiuneUndo {
private:
    Oferta addedOferta;
    OfertaRepo& ofertaRepo;
public:
    UndoAdauga(const Oferta& oferta, OfertaRepo& repo) : addedOferta{ oferta }, ofertaRepo{ repo } {}

    void doUndo() override {
        this->ofertaRepo.sterge(this->addedOferta.getDenumire(), this->addedOferta.getDestinatie());
    }
};

class UndoDelete : public ActiuneUndo {
private:
    Oferta deletedOferta;
    OfertaRepo& ofertaRepo;
public:
    UndoDelete(const Oferta& oferta, OfertaRepo& repo) : deletedOferta{ oferta }, ofertaRepo{ repo } {}

    void doUndo() override {
        this->ofertaRepo.store(this->deletedOferta);
    }
};

class UndoModifica : public ActiuneUndo {
private:
    Oferta modifiedOferta;
    OfertaRepo& ofertaRepo;
    int pret_vechi;
public:
    UndoModifica(Oferta& oferta, OfertaRepo& repo, int p) : modifiedOferta{ oferta }, ofertaRepo{ repo }, pret_vechi{ p } {}

    void doUndo() override {
        this->ofertaRepo.modify(this->modifiedOferta.getDenumire(), this->modifiedOferta.getDestinatie(), pret_vechi);
    }
};