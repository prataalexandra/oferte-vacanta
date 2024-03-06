#include "Repo.h"
#include <assert.h>
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

void OfertaRepo::store(const Oferta& p)
{
	if (exist(p)) {
		throw OfertaException("Exista deja oferta cu denimirea: " + p.getDenumire() + " si destinatia: " + p.getDestinatie());
	}
	all.push_back(p);
	metoda1();
}

void OfertaRepo::sterge(const string& denumire, const string& destinatie) {
	auto it = std::remove_if(all.begin(), all.end(), [&](const Oferta& oferta) {
		return oferta.getDenumire() == denumire && oferta.getDestinatie() == destinatie;
		});
	if (it == all.end()) {
		throw OfertaException("Nu exista oferta cu denumirea: " + denumire + " si destinatia: " + destinatie);
	}
	all.erase(it, all.end());
	metoda1();
}

void OfertaRepo::modify(const string& denumire, const string& destinatie, int pret) {
	try {
		auto it = std::find_if(all.begin(), all.end(), [&](const Oferta& oferta) {
			return oferta.getDenumire() == denumire && oferta.getDestinatie() == destinatie;
			});
		if (it == all.end()) {
			throw OfertaException("Oferta nu exista in repo!");
		}
		it->setPret(pret);
		metoda1();
	}
	catch (const OfertaException&) {
		throw OfertaException("Oferta nu exista in repo!");
	}

}


bool OfertaRepo::exist(const Oferta& p) const {
	try {
		find(p.getDenumire(), p.getDestinatie());
		return true;
	}
	catch (OfertaException&) {
		return false;
	}
}

int OfertaRepo::caut_poz(const string& denumire, const string& destinatie)
{
	for (int i = 0; i < all.size(); i++)
		if (all[i].getDenumire() == denumire && all[i].getDestinatie() == destinatie)
			return i;
	return -1;
}

const Oferta& OfertaRepo::find(string denumire, string destinatie) const {
	for (const auto& p : all) {
		if (p.getDenumire() == denumire && p.getDestinatie() == destinatie) {
			return p;
		}
	}
	//daca nu exista arunc o exceptie
	throw OfertaException("Nu exista oferta denumire: " + denumire + " si destinatie: " + destinatie);
}


const vector<Oferta>& OfertaRepo::getAll() const noexcept {
	return all;
}


ostream& operator<<(ostream& out, const OfertaException& ex) {
	out << ex.msg;
	return out;
}

void OfertaRepo::metoda1() {
	cout << "bbb!\n";
}


void testAdauga() {
	OfertaRepo rep;
	rep.store(Oferta{ "a","a","a",4 });
	assert(rep.getAll().size() == 1);
	assert(rep.find("a", "a").getDenumire() == "a");

	rep.store(Oferta{ "b","b","b",4 });
	assert(rep.getAll().size() == 2);

	try {
		rep.store(Oferta{ "a","a","a",4 });
		assert(false);
	}
	catch (const OfertaException&) {
		assert(true);
	}
	try {
		rep.find("c", "c");
		assert(false);
	}
	catch (const OfertaException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
}

void testCauta() {
	OfertaRepo rep;
	rep.store(Oferta{ "a","a","a",4 });
	rep.store(Oferta{ "b","b","b",4 });

	auto p = rep.find("a", "a");
	assert(p.getDenumire() == "a");
	assert(p.getDestinatie() == "a");

	try {
		rep.find("a", "b");
		assert(false);
	}
	catch (OfertaException&) {
		assert(true);
	}
}



void testeRepo() {
	testAdauga();
	testCauta();
}