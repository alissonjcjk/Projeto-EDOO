#pragma once
#include <vector>
#include "Funcionarios.h"
#include <iostream>

using namespace std;


class Barbeiro: public Funcionarios{
    private:
        //agendamentos
    public:
        bool estaDisponivel(int horario);
};