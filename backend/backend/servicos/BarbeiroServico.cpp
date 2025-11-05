#include "BarbeiroServico.h"
#include "../utils/EmailUtils.h"
#include <algorithm>
#include <cctype>

BarbeiroService::BarbeiroService(BarbeiroRepository& r) : repo(r) {}

int BarbeiroService::criarBarbeiro(Barbeiro barbeiro) {
    if (barbeiro.getNome().empty() || barbeiro.getEmail().empty()) return -1;
    if (!utils::EmailUtils::isEmailValido(barbeiro.getEmail())) return -1;
    if (barbeiro.getSalario() < 0) return -1;

    return repo.createBarbeiro(barbeiro);
}

Barbeiro BarbeiroService::buscarPorId(int id) {
    return repo.buscarPorId(id);
}

std::vector<Barbeiro> BarbeiroService::listarBarbeiros() {
    return repo.findAllBarbeiros();
}