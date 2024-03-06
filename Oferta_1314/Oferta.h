#pragma once
#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Oferta {
	std::string denumire;
	std::string destinatie;
	std::string tip;
	int pret;
public:
	Oferta(const string n, const string d, string t, int p) :denumire{ n }, destinatie{ d }, tip{ t }, pret{ p } {}

	Oferta(const Oferta& ot) :denumire{ ot.denumire }, destinatie{ ot.destinatie }, tip{ ot.tip }, pret{ ot.pret } {
		cout << "!!!!!!!!!!!!!!!!!!!!\n";
	}


	string getTip() const {
		return tip;
	}
	string getDestinatie() const {
		return destinatie;
	}
	string getDenumire() const {
		return denumire;
	}

	int getPret() const noexcept {
		return pret;
	}

	void setTip(const string& newTip) {
		tip = newTip;
	}

	void setDenumire(const string& newDenumire) {
		denumire = newDenumire;
	}
	void setDestinatie(const string& newDestinatie) {
		destinatie = newDestinatie;
	}
	void setPret(int newPret) {
		pret = newPret;
	}
};

bool cmpDenumire(const Oferta& p1, const Oferta& p2);


bool cmpDestinatie(const Oferta& p1, const Oferta& p2);

