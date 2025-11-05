#include "GestorServico.h"
#include <cpprest/json.h>
#include "../utils/EmailUtils.h"
#include "../modelos/Gestor.h"

GestorService::GestorService(GestorRepositorio& r) : repo(r) {}

int GestorService::criarGestor(Gestor gestor) {
	if (gestor.getNome().empty() || gestor.getEmail().empty()) return -1;
	if (!utils::EmailUtils::isEmailValido(gestor.getEmail())) return -1;
	if (gestor.getSalario() < 0) return -1;
	return repo.criarGestor(gestor);
}

std::vector<Gestor> GestorService::listarGestores() {
	return repo.findAllGestores();
}