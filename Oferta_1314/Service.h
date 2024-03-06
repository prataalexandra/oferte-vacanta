#pragma once
#pragma once
#include "Oferta.h"
#include "Repo.h"
#include "Undo_Nou.h"
#include <string>
#include <vector>
#include <map>

#include <functional>
#include "validator.h"

using std::map;
using std::vector;
using std::function;

class Agentie {
	OfertaRepo& rep;
	Validator& val;
	map<string, int> stats;
	vector<Oferta> generalSort(bool (*maiMicF)(const Oferta&, const Oferta&));

	vector<Oferta> filtreaza(function<bool(const Oferta&)> fct);

	vector<std::unique_ptr<ActiuneUndo>> undoList;

public:
	Agentie(OfertaRepo& rep, Validator& val) :rep{ rep }, val{ val } {
	}

	Agentie(const Agentie& ot) = delete;

	const vector<Oferta>& getAll() noexcept {
		return rep.getAll();
	}

	vector<Oferta> get_all_service();

	void addOferta(const string& denumire, const string& destinatie, const string& tip, int pret);
	void stergeOferta(const string& denumire, const string& destinatie);
	void modificaOferta(const string& denumire, const string& destinatie, int pret);
	//void modificaOferta(const string& denumire, const string& destinatie, const string& denumire_noua, const string& destinatie_noua, const string& tip, int pret_nou);

	const Oferta& search_service(const string& name, const string& producer) const;
	map<string, int> getStats();

	void adaugaStatistica(const string& destinatie);

	void stergeStatistica(const string& destinatie);

	vector<Oferta> sortDenumire();


	vector<Oferta> sortDestinatie();

	void populate();

	vector<Oferta> sortTipPret();


	vector<Oferta> filtrarePretMaiMic(int pret);


	vector<Oferta> filtrarePret(int pretMin, int pretMax);

	void undo();

};
void testCtr();
