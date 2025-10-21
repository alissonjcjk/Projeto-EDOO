#include "Barbeiro.h"
#include <iostream>
using namespace std;


bool Barbeiro::agendar(string nome, int horario){
    agendamento temp;
    if(horario <= getHorarioTrabalhoFinal() && horario >= getHorarioTrabalhoInicial()){
        if(estaDisponivel(horario)){
            temp.nome = nome;
            temp.horario = horario;
            agendamentos.push_back(temp);
        }
    }else{
        return false;
    }
}

bool Barbeiro::estaDisponivel(int horario){
    for(int i=0;i<agendamentos.size();i++){
        if(horario == agendamentos[i].horario){
            return false;
        }
    }
    return true;
}