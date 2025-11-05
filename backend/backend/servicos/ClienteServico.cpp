#include "ClienteServico.h"
#include "../utils/EmailUtils.h"
#include <algorithm>
#include <cctype>

ClienteServico::ClienteServico(ClienteRepositorio& r): repo(r) {}

int ClienteServico::cria(Cliente cliente, int servicoPreferidoId) {
    if (cliente.getNome().empty() || cliente.getEmail().empty()) return -1;
    if (!utils::EmailUtils::isEmailValido(cliente.getEmail())) return -1;

    return repo.criar(cliente, servicoPreferidoId);
}

Cliente ClienteServico::buscarPor(int id) {
    return repo.buscarPorId(id);
}

std::vector<Cliente> ClienteServico::listarClientes() {
    return repo.findAllClientes();
}

int ClienteServico::deletar(int idCliente) {
    return repo.deletar(idCliente);
}