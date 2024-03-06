#include "RepoCos.h"
#include "Service.h"
#include "Repo.h"
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <random>





void CosRepo::cos_add(const string& denumire, const string& destinatie)
{
	const int ind = repo.caut_poz(denumire, destinatie);
	if (ind == -1) throw OfertaException("Eroare! Elementul nu poate fi adaugat in cos pentru ca nu exista!");
	else
	{
		cos.push_back(repo.find(denumire, destinatie));
	}
}

const vector<Oferta>& CosRepo::cos_get_all() const noexcept
{
	return cos;
}


void CosRepo::delete_cos() noexcept
{
	cos.clear();
}

void CosRepo::generate_cos()
{
	const int lungime = int(repo.getAll().size());
	if (lungime == 0 || lungime == 1)
		throw OfertaException("Eroare! Nu exista destule oferte care pot fi adaugate!");
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> dist(1, lungime - 1);
	//std::uniform_int_distribution<> frecv(1, 10);
	int nr_elem = dist(mt);
	while (nr_elem)
	{
		const int ind_produs = dist(mt);
		//const int nr_produse = frecv(mt);
		cos_add(repo.getAll()[ind_produs].getDenumire(), repo.getAll()[ind_produs].getDestinatie());
		nr_elem--;
	}
}

void test_repo_cos()
{
	OfertaRepo repo;
	CosRepo cos_repo{ repo };
	Validator val;
	Agentie serv{ repo, val };
	//repo cart
	try
	{
		cos_repo.generate_cos(); assert(false);
	}
	catch (const OfertaException&) { assert(true); };


	repo.store(Oferta{ "Oferta 1", "Destinatie 1", "Tip 1", 100 });
	repo.store(Oferta{ "Oferta 2", "Destinatie 1", "Tip 2", 200 });
	repo.store(Oferta{ "Oferta 3", "Destinatie 2", "Tip 3", 300 });
	repo.store(Oferta{ "Oferta 4", "Destinatie 2", "Tip 4", 400 });

	assert(cos_repo.cos_get_all().size() == 0);
	cos_repo.cos_add("Oferta 1", "Destinatie 1");
	cos_repo.cos_add("Oferta 2", "Destinatie 1");
	cos_repo.cos_add("Oferta 3", "Destinatie 2");

	assert(cos_repo.cos_get_all().size() == 3);

	try
	{
		cos_repo.cos_add("aa", "aa"); assert(false);
	}
	catch (const OfertaException&)
	{
		assert(true);
	}

	cos_repo.delete_cos();
	assert(cos_repo.cos_get_all().size() == 0);

	cos_repo.generate_cos();
	assert(cos_repo.cos_get_all().size() > 0);

	cos_repo.delete_cos();
}