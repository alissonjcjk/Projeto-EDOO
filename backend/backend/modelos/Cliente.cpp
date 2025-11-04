#include "Cliente.h"


Cliente::Cliente(int i, const string& n, const string& e, const string& t, int s)
    : Pessoa(i, n, e, t), servicoPreferido(s) {
}

Cliente::Cliente(const string& n, const string& e, const string& t, int s)
    : Pessoa(n, e, t), servicoPreferido(s) {
}


Cliente::Cliente() : Pessoa() {}

// Setter
//void Cliente::setServicoPreferido(int servico) { this->servicoPreferido = servico; }

// Getter
int Cliente::getServicoPreferido() const { return servicoPreferido; }