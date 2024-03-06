#include "Service_Cos.h" 
#include <fstream>
#include "Service.h"
#include <assert.h>


void CosService::cos_add_service(const string& nume, const string& producator)
{
	valid.validate_cart(nume, producator);
	repo.cos_add(nume, producator);
}


const vector<Oferta>& CosService::cos_get_all_service() noexcept
{
	return repo.cos_get_all();
}


void CosService::cos_delete_service() noexcept
{
	repo.delete_cos();
}

void CosService::cos_generate_service()
{
	repo.generate_cos();
}

void teste_service_cos()
{
	OfertaRepo repo;
	CosRepo cos_repo{ repo };
	Validator valid;
	Agentie serv{ repo, valid };
	CosService cos_serv{ cos_repo,valid };

	repo.store(Oferta{ "Oferta 1", "Destinatie 1", "Tip 1", 100 });
	repo.store(Oferta{ "Oferta 2", "Destinatie 1", "Tip 2", 200 });
	repo.store(Oferta{ "Oferta 3", "Destinatie 2", "Tip 3", 300 });
	repo.store(Oferta{ "Oferta 4", "Destinatie 2", "Tip 4", 400 });

	cos_serv.cos_add_service("Oferta 1", "Destinatie 1");
	cos_serv.cos_add_service("Oferta 2", "Destinatie 1");
	cos_serv.cos_add_service("Oferta 3", "Destinatie 2");

	assert(cos_serv.cos_get_all_service().size() == 3);


	cos_serv.cos_delete_service();
	assert(cos_serv.cos_get_all_service().size() == 0);

	cos_serv.cos_generate_service();
	assert(cos_serv.cos_get_all_service().size() > 0);
}

void CosService::exportToFile(const string& fileName) {
	std::ofstream fout(fileName);

	if (!fout.is_open()) {
		throw OfertaException("Error open: " + fileName);
	}

	for (const auto& oferta : this->repo.cos_get_all())
	{
		cout << oferta.getDenumire() << "," << oferta.getDestinatie() << "," << oferta.getTip() << "," << oferta.getPret() << "\n";
		fout << oferta.getDenumire() << "," << oferta.getDestinatie() << "," << oferta.getTip() << "," << oferta.getPret() << "\n";
	}
	fout.close();
}