#pragma once
#pragma once
#include "RepoCos.h"
#include "Validator.h"
//Serviceul cosului de cumparaturi


class CosService : public Observable
{
private:

	CosRepo& repo;
	Validator& valid;

public:
	//Constructorul clasei
	CosService(CosRepo& rep, Validator& val) noexcept : repo{ rep }, valid{ val } {}

	//Nu permitem copierea
	CosService(const CosService& other) = delete;

	/*
	* Functia de adaugare a unui produs valid
	*  -> arunca eroare daca produsul nu a putut fi adaugat
	*/
	void cos_add_service(const string& name, const string& producer);

	/*
	* Functia returneaza cosul din repository.
	*/
	const vector<Oferta>& cos_get_all_service() noexcept;

	/*
	* Functia goleste cosul de cumparaturi
	*/
	void cos_delete_service() noexcept;

	/*
	* Functia genereaza un cos cu produse la intamplare
	*/
	void cos_generate_service();
	void exportToFile(const string& fileName);
};

void teste_service_cos();