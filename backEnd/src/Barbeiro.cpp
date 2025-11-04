#include "Barbeiro.h"
#include "Agendamento.h"
#include "Barbeiro.h"
#include "Cliente.h"
#include "Servico.h"
#include <iostream>
using namespace std;


Barbeiro::Barbeiro(int horarioInicio, int horarioFIm, int id, string nome, string email, string telefone, string especialidade):
Funcionarios(horarioInicio,horarioFIm,id,nome,email,telefone){
    this->especialidade = especialidade;
}

string Barbeiro::getEspecialidade() const{
    return especialidade;
}


