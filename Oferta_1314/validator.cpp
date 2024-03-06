#include "validator.h"
#include <assert.h>
#include <sstream>

void Validator::validate(const Oferta& p) {
	vector<string> msgs;
	if (p.getPret() < 0) msgs.push_back("Pret negativ!!!");
	if (p.getTip().size() == 0) msgs.push_back("Tip vid!!!");
	if (p.getDenumire().size() == 0) msgs.push_back("Denumire vid!!!");
	if (p.getDestinatie().size() == 0)msgs.push_back("Destinatie vid!!!");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}


void Validator::validate_cart(const string& denumire, const string& destinatie)
{
	vector<string> errors;
	if (denumire.size() == 0) errors.push_back("Eroare! Denumire invalida!");
	if (destinatie.size() == 0) errors.push_back("Eroare! Destinatie invalida!");
	if (errors.size() > 0) throw ValidateException(errors);
}


ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

void testValidator() {
	Validator v;
	Oferta p{ "","","", -1 };
	try {
		v.validate(p);
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		auto mesaj = sout.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
	}

}