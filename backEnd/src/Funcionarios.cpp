#include "Pessoa.h"
#include "Funcionarios.h"
#include <iostream>

using namespace std;

//seta o horario de funcionamento
Funcionarios::Funcionarios(int horarioInicio, int horarioFin, int id, string nome, string email, string telefone):Pessoa(id,nome,email,telefone){
    horarioTrabalhoInicio = horarioInicio;
    horarioTrabalhoTermino = horarioFin;
}


int Funcionarios::getHorarioTrabalhoFinal() const{
    return horarioTrabalhoTermino;
}

int Funcionarios::getHorarioTrabalhoInicial() const{
    return horarioTrabalhoInicio;
}

float Funcionarios::getSalario() const{
    return salario;
}
