#include "Pessoa.h"
#include "Funcionarios.h"
#include <iostream>

using namespace std;

//seta o horario de funcionamento
Funcionarios::Funcionarios(int horarioInicio, int horarioFin, int id, string nome, string email, string telefone):Pessoa(id,nome,email,telefone){
    horarioTrabalhoInicio = horarioInicio;
    horarioTrabalhoTermino = horarioFin;
}

//procura o funcionario na alocação dinâmica e retorna true se a demição for bem concluida
bool Funcionarios::serDemitido(string nome){
    for(int i=0;i<funcionarios.size();i++){
        if(funcionarios[i]->getNome() == nome){
            funcionarios.erase(funcionarios.begin() + i);
            return true;
        }
    }
    return false;
}

int Funcionarios::getHorarioTrabalhoFinal(){
    return horarioTrabalhoTermino;
}

int Funcionarios::getHorarioTrabalhoInicial(){
    return horarioTrabalhoInicio;
}

float Funcionarios::getSalario(){
    return salario;
}
//retorna true se o aumento de salario for bem concluido
bool Funcionarios::aumentarSalario(float valor, string nome){
    for(int i=0;i<funcionarios.size();i++){
        if(funcionarios[i]->getNome() == nome){
            salario += valor;
            return true;
        }
    }
    return false;
}
    Funcionarios::~Funcionarios(){
        for (int i = 0; i < funcionarios.size(); i++)
        {
            delete funcionarios[i];
        }
        
}