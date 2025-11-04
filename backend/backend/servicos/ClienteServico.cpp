#include "ClienteServico.h"
#include "../utils/EmailUtils.h"
#include <algorithm>
#include <cctype>

ClienteServico::ClienteServico(ClienteRepositorio& r): repo(r) {}

int ClienteServico::cria(Cliente cliente) {
    if (cliente.getNome().empty() || cliente.getEmail().empty()) return -1;
    if (!utils::EmailUtils::isEmailValido(cliente.getEmail())) return -1;

    return repo.criar(cliente);
}

Cliente ClienteServico::buscarPor(int id) {
    return repo.buscarPorId(id);
}

std::vector<Cliente> ClienteServico::listarClientes() {
    return repo.findAllClientes();
}