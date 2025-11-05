#include "Cliente.h"

Cliente::Cliente(int i, const std::string& n, const std::string& e, const std::string& t, const Servicos& s)
    : Pessoa(i, n, e, t), servicoPreferido(s) {
}

Cliente::Cliente(const std::string& n, const std::string& e, const std::string& t, const Servicos& s)
    : Pessoa(n, e, t), servicoPreferido(s) {
}

Cliente::Cliente() : Pessoa(), servicoPreferido() {}

// Setter
//void Cliente::setServicoPreferido(int servico) { this->servicoPreferido = servico; }

// Getter
std::string Cliente::getServicoPreferidoNome() const { return servicoPreferido.getNome(); }