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
        string especialidade;
    public:
        Barbeiro(int horarioInicio, int horarioFIm, int id, string nome, string email, string telefone, string especialidade);

        string getEspecialidade() const;
};