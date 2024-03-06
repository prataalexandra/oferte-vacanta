#pragma once
#pragma once
#include "Oferta.h"
#include "Repo.h"
#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include "Observer.h"
using std::string;
using std::vector;
using std::ostream;
class CosRepo : public Observable
{
private:

	vector <Oferta> cos;
	OfertaRepo& repo;

	/*
	* Functia cauta un anumit produs daca se afla in cos si ii returneaza pozitia altfel returneaza -1
	*/
	//int cos_cauta_ind(const string& name, const string& producer);

public:
	//Constructorul clasei
	CosRepo(OfertaRepo& rep) noexcept : repo{ rep } {}

	//Nu se permite copierea repository-ului
	CosRepo(const CosRepo& other) = delete;

	/*
	* Functia adauga in cos un produs de "nr" ori
	*/
	void cos_add(const string& nume, const string& producator);

	/*
	* Functia sterge toate elementele din cos
	*/
	void delete_cos() noexcept;

	/*
	* Functia genereaza un cos cu produse random
	*/
	void generate_cos();

	/*
	* Functia returneaza cosul de cumparaturi
	*/
	const vector<Oferta>& cos_get_all() const noexcept;


};

void test_repo_cos();