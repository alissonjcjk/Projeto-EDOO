#include "Pessoa.h"
#include "Funcionarios.h"
#include <iostream>

using namespace std;

Funcionarios::Funcionarios(float salario,string funcao, string nome, string email):Pessoa(nome,email){
    this->salario = salario;
    qtdFunfionarios = 0;
    funcio[qtdFunfionarios].nome = nome;
    funcio[qtdFunfionarios].funcao = funcao;
}

//adiciona mais um funcionario
void Funcionarios::addFuncionario(string nome, string funcao){
    qtdFunfionarios++;
    funcio[qtdFunfionarios].nome = nome;
    funcio[qtdFunfionarios].funcao = funcao;
}

float Funcionarios::getSalario(){
    return salario;
}
