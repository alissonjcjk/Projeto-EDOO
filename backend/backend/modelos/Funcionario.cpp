#include "Funcionario.h"
#include "Pessoa.h"
#include <iostream>

using namespace std;

Funcionario::Funcionario(int id, string nome, string email, string telefone, float salario) :Pessoa(id, nome, email, telefone) {
    salario = salario;
}

Funcionario::Funcionario(string nome, string email, string telefone, float salario) : Pessoa(nome, email, telefone) {
    salario = salario;
}

Funcionario::Funcionario()
    : Pessoa(), salario(0.0f) {}

bool Funcionario::serDemitido(string nome) {
    for (int i = 0; i < funcionarios.size(); i++) {
        if (funcionarios[i]->getNome() == nome) {
            funcionarios.erase(funcionarios.begin() + i);
            return true;
        }
    }
    return false;
}

float Funcionario::getSalario() const {
    return salario;
}

bool Funcionario::aumentarSalario(float valor, string nome) {
    for (int i = 0; i < funcionarios.size(); i++) {
        if (funcionarios[i]->getNome() == nome) {
            salario += valor;
            return true;
        }
    }
    return false;
}
Funcionario::~Funcionario() {
    for (int i = 0; i < funcionarios.size(); i++)
    {
        delete funcionarios[i];
    }

}