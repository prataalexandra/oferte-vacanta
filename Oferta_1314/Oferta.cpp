#include "Oferta.h"


bool cmpDenumire(const Oferta& p1, const Oferta& p2) {
	return p1.getDenumire() < p2.getDenumire();
}

bool cmpDestinatie(const Oferta& p1, const Oferta& p2) {
	return p1.getPret() < p2.getPret();
}