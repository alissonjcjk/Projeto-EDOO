#include "Pessoa.h"
#include "Funcionarios.h"
#include <iostream>

using namespace std;

Funcionarios::Funcionarios(float salario, string funcio, string email):Pessoa(funcio,email){
    this->salario = salario;
    qtdFunfionarios = 0;
}

void Funcionarios::addFuncionario(){
    qtdFunfionarios++;
}

float Funcionarios::getSalario(){
    return salario;
}
