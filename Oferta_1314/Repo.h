#pragma once
#pragma once
#include "Oferta.h"

#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class RepoAbstract {
public:

	virtual void metoda1() = 0;



	virtual ~RepoAbstract() = default;
};

class OfertaRepo : public RepoAbstract {
	vector<Oferta> all;
	/*
	metoda privata verifica daca exista deja p in repository
	*/
	bool exist(const Oferta& p) const;
public:
	OfertaRepo() = default;

	OfertaRepo(const OfertaRepo& ot) = delete;

	void store(const Oferta& p);

	void sterge(const string& denumire, const string& destinatie);
	void modify(const string& denumire, const string& destinatie, int newPret);


	const Oferta& find(string type, string species) const;

	int caut_poz(const string& denumire, const string& destinatie);

	const vector<Oferta>& getAll() const noexcept;

	void metoda1() override;

};




class OfertaException {
	string msg;
public:
	OfertaException(string m) :msg{ m } {}
	friend ostream& operator<<(ostream& out, const OfertaException& ex);
};

ostream& operator<<(ostream& out, const OfertaException& ex);

void testeRepo();