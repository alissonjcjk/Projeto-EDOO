#pragma once

#include <vector>
#include "Funcionario.h"
#include "Agendamento.h"
#include <iostream>

using namespace std;

class Barbeiro : public Funcionario {
private:
    // agendamentos
    std::vector<Agendamento> agendamentos;
public:
    Barbeiro(int id, const std::string& nome, const std::string& email,
        const std::string& telefone, float salario,
        const std::vector<Agendamento>& agendamentos = {});

    Barbeiro(const std::string& nome, const std::string& email,
        const std::string& telefone, float salario,
        const std::vector<Agendamento>& agendamentos = {});

    Barbeiro()
        : Funcionario(), agendamentos({}) {};

    bool estaDisponivel(int horario);
};