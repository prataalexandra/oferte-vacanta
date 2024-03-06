#pragma once
#pragma once
#include <string>
#include "Oferta.h"
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class ValidateException {
	vector<string> msgs;
public:
	ValidateException(const vector<string>& errors) :msgs{ errors } {}
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class Validator {
public:
	void validate(const Oferta& p);
	void validate_cart(const string& denumire, const string& destinatie);
};

void testValidator();