#include "Cliente.h"

// Construtor
Cliente::Cliente(int i, const string& n, const string& e, const string& t, const string& s)
    : Pessoa(i, n, e, t), servicoPreferido(s) {}

// Setter
void Cliente::setServicoPreferido(const string& servico) {this->servicoPreferido = servico;}

// Getter
string Cliente::getServicoPreferido() const { return servicoPreferido;}