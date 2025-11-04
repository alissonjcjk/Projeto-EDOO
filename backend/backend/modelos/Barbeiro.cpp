#include "Barbeiro.h"
#include <iostream>
using namespace std;

Barbeiro::Barbeiro(int id, const std::string& nome,
    const std::string& email, const std::string& telefone,
    float salario, const std::vector<Agendamento>& agendamentos)
    : Funcionario(id, nome, email, telefone, salario), agendamentos(agendamentos) {}

Barbeiro::Barbeiro(const std::string& nome,
    const std::string& email, const std::string& telefone,
    float salario, const std::vector<Agendamento>& agendamentos)
    : Funcionario(nome, email, telefone, salario), agendamentos(agendamentos) {}

bool Barbeiro::estaDisponivel(int horario) {

    return true;
}