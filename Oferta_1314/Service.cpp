#include "Service.h"
#include <functional>
#include <algorithm>
#include <assert.h>

vector<Oferta> Agentie::generalSort(bool(*maiMicF)(const Oferta&, const Oferta&)) {
	vector<Oferta> v{ rep.getAll() };
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!maiMicF(v[i], v[j])) {

				Oferta aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}

void Agentie::populate() {
	Oferta p{ "Excursie","b","c",30 };
	rep.store(p);
	Oferta p1{ "City Break","b2","c",30 };
	rep.store(p1);
	Oferta p2{ "a3","b3","c",30 };
	rep.store(p2);
	Oferta p3{ "a4","b4","c",30 };
	rep.store(p3);
	Oferta p4{ "a5","b5","d",30 };
	rep.store(p4);
	Oferta p5{ "a6","b6","d",30 };
	rep.store(p5);
	Oferta p6{ "a7","b7","d",30 };
	rep.store(p6);
}


void Agentie::addOferta(const string& denumire, const string& destinatie, const string& tip, int pret) {
	Oferta p{ denumire,destinatie,tip,pret };
	val.validate(p);
	rep.store(p);
	this->undoList.push_back(std::make_unique<UndoAdauga>(UndoAdauga{ p,rep }));
	adaugaStatistica(p.getDestinatie());
}



void Agentie::stergeOferta(const std::string& denumire, const std::string& destinatie) {
	Oferta p = rep.find(denumire, destinatie);
	rep.sterge(denumire, destinatie);
	this->undoList.push_back(std::make_unique<UndoDelete>(UndoDelete{ p,rep }));
	stergeStatistica(destinatie);
}

void Agentie::modificaOferta(const string& denumire, const string& destinatie, int pret)
{
	Oferta p = rep.find(denumire, destinatie);
	int pret_vechi = p.getPret();
	//string tip_vechi = p.getTip();
	//int pret_vechi = p.getPret();
	rep.modify(denumire, destinatie, pret);
	//Oferta p2 = rep.find(denumire_noua, destinatie_noua);
	this->undoList.push_back(std::make_unique<UndoModifica>(UndoModifica{ p,rep,pret_vechi }));
	//stergeStatistica(destinatie);
	//adaugaStatistica(destinatie_noua);
}

vector<Oferta> Agentie::sortDenumire() {
	auto copyAll = rep.getAll();
	std::sort(copyAll.begin(), copyAll.end(), cmpDenumire);
	return copyAll;

}


vector<Oferta> Agentie::sortDestinatie() {
	return generalSort(cmpDestinatie);
}



vector<Oferta> Agentie::sortTipPret() {
	return generalSort([](const Oferta& p1, const Oferta& p2) {
		if (p1.getTip() == p2.getTip()) {
			return p1.getPret() < p2.getPret();
		}
		return p1.getTip() < p2.getTip();
		});
}

vector<Oferta> Agentie::filtreaza(function<bool(const Oferta&)> fct) {
	vector<Oferta> rez;
	for (const auto& pet : rep.getAll()) {
		if (fct(pet)) {
			rez.push_back(pet);
		}
	}
	return rez;
}

vector<Oferta> Agentie::filtrarePretMaiMic(int pret) {
	return filtreaza([pret](const Oferta& p) {
		return p.getPret() < pret;
		});
}

vector<Oferta> Agentie::filtrarePret(int pretMin, int pretMax) {
	return filtreaza([=](const Oferta& p) {
		return p.getPret() >= pretMin && p.getPret() <= pretMax;
		});
}

void Agentie::adaugaStatistica(const string& destinatie)
{
	stats[destinatie]++;
}

void Agentie::stergeStatistica(const string& destinatie)
{
	stats[destinatie]--;
}

map<string, int> Agentie::getStats() {
	return stats;
}

void Agentie::undo() {
	if (undoList.empty()) {
		throw OfertaException("Nu mai exista operatii.");
	}

	// instantiem un pointer catre obiectul ActiuneUndo pe care trebuie sa-l folosim
	// std::unique_ptr<ActiuneUndo> undoAction = std::make_unique<ActiuneUndo>(this->undoList.back());
	this->undoList.back()->doUndo();
	this->undoList.pop_back();
}
vector<Oferta> Agentie::get_all_service()
{
	return rep.getAll();
}

const Oferta& Agentie::search_service(const string& name, const string& producer) const
{
	return rep.find(name, producer);
}

void testAdaugaCtr() {
	OfertaRepo rep;
	Validator val;
	Agentie ctr{ rep,val };
	ctr.addOferta("a", "a", "a", 6);
	assert(ctr.getAll().size() == 1);


	try {
		ctr.addOferta("", "", "", -1);
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}

	try {
		ctr.addOferta("a", "a", "a", -1);
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
}

void testFiltrare() {
	OfertaRepo rep;
	Validator val;
	Agentie ctr{ rep,val };
	ctr.addOferta("a", "a", "a", 6);
	ctr.addOferta("b", "a", "c", 60);
	ctr.addOferta("c", "a", "b", 600);
	assert(ctr.filtrarePret(6, 70).size() == 2);
	assert(ctr.filtrarePret(6, 60).size() == 2);
	assert(ctr.filtrarePretMaiMic(60).size() == 1);
	assert(ctr.filtrarePretMaiMic(7).size() == 1);
	assert(ctr.filtrarePretMaiMic(6).size() == 0);
}

void testSortare() {
	OfertaRepo rep;
	Validator val;
	Agentie ctr{ rep,val };
	ctr.addOferta("z", "z", "z", 6);
	ctr.addOferta("b", "a", "b", 60);
	ctr.addOferta("c", "a", "b", 600);

	auto firstP = ctr.sortDenumire()[0];
	assert(firstP.getDenumire() == "b");

	firstP = ctr.sortDestinatie()[0];
	assert(firstP.getDestinatie() == "z");

	firstP = ctr.sortTipPret()[0];
	assert(firstP.getPret() == 60);

}

void testSterge() {

	OfertaRepo repo;
	Validator val;
	Agentie ctr{ repo,val };
	repo.store(Oferta{ "Excursie", "Destinatie 1", "Tip 1", 100 });
	repo.store(Oferta{ "City Break", "Destinatie 1", "Tip 2", 200 });
	repo.store(Oferta{ "Oferta 3", "Destinatie 2", "Tip 3", 300 });
	repo.store(Oferta{ "Oferta 4", "Destinatie 2", "Tip 4", 400 });


	ctr.stergeOferta("Oferta 1", "Destinatie 1");
	assert(repo.getAll().size() == 3);


	try {
		ctr.stergeOferta("Oferta 5", "Destinatie 3");
	}
	catch (OfertaException&) {
		assert(true);
	}
}

/*void testOfertaRepoModify() {
	OfertaRepo repo;
	Validator val;
	Agentie ctr{ repo,val };
	repo.store(Oferta("oferta1", "destinatie1", "tip1", 100));
	repo.store(Oferta("oferta2", "destinatie2", "tip2", 200));


	ctr.modificaOferta("oferta1", "destinatie1", "newDenumire", "newDestinatie", "newTip", 300);
	const Oferta& oferta1 = repo.find("newDenumire", "newDestinatie");
	assert(oferta1.getDenumire() == "newDenumire");
	assert(oferta1.getDestinatie() == "newDestinatie");
	assert(oferta1.getTip() == "newTip");
	assert(oferta1.getPret() == 300);


	try {
		ctr.modificaOferta("nonexisting", "oferta", "test", "test", "bwa", 200);
		assert(false);
	}
	catch (const OfertaException&) {
		assert(true);
	}
}*/

void undoTests() {
	OfertaRepo repo;
	Validator val;
	Agentie ctr{ repo,val };

	ctr.addOferta("oferta1", "destinatie1", "tip1", 100);

	ctr.undo();
	assert(ctr.getAll().empty());

	ctr.addOferta("oferta2", "destinatie2", "tip2", 100);

	ctr.stergeOferta("oferta2", "destinatie2");
	assert(ctr.getAll().empty());
	ctr.undo();
	assert(!ctr.getAll().empty());


	/*ctr.modificaOferta("oferta2", "destinatie2", "oferta1", "destinatie1", "bwa", 27);
	assert(ctr.getAll()[0].getDenumire() == "oferta1");
	//cout << ctr.getAll()[0].getDenumire();
	ctr.undo();
	//assert(ctr.getAll()[0].getDenumire() == "oferta2");
	*/
}

void testCtr() {
	testAdaugaCtr();
	testFiltrare();
	testSortare();
	testSterge();
	//testOfertaRepoModify();
	undoTests();
}