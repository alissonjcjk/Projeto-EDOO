#pragma once
#include <vector>
#include "Funcionarios.h"
#include <iostream>

using namespace std;
struct agendamento
{
    string nome;
    int horario;
};


class Barbeiro: public Funcionarios{
    private:
        vector <agendamento> agendamentos;
    public:
        bool agendar(string nome, int horario);
        bool estaDisponivel(int horario);
};