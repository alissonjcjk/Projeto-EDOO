#include "Gestor.h"
#include <iostream>
#include "Funcionarios.h"
#include "Barbeiro.h"

using namespace std;

Gestor::Gestor(int horarioInicio, int horarioFIm, int id, string nome, string email, string telefone):
Funcionarios(horarioInicio,horarioFIm,id,nome,email,telefone){};

vector <Barbeiro> Gestor::demitir(vector <Barbeiro> barbeiros, string nome){
    for(int i=0; i<barbeiros.size(); i++){
        if(barbeiros[i].getNome() == nome){
            barbeiros.erase(barbeiros.begin()+i);
            return barbeiros;
        }
    }
    return barbeiros;
}