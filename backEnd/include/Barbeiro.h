#pragma once
#include <vector>
#include "Agendamento.h"
#include "Funcionarios.h"
#include <iostream>

using namespace std;


class Barbeiro: public Funcionarios{
    private:

    public:
        Barbeiro(int horarioInicio, int horarioFIm, int id, string nome, string email, string telefone);
};