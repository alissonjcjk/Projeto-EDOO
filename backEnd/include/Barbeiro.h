#pragma once
#include <vector>
// #include "Agendamento.h"
#include "Funcionarios.h"
#include <iostream>

using namespace std;

class Agendamento;
class Barbeiro;
class Cliente;
class Servico;

class Barbeiro: public Funcionarios{
    private:
        Agendamento *agendamento;
    public:
        Barbeiro(int horarioInicio, int horarioFIm, int id, string nome, string email, string telefone);

        //void setAgendamento(int id, Cliente* cliente, Barbeiro* barbeiro, Servico* servico, const string& data, const string& horarioInicio, const string& horarioFim);
};