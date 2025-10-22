#include "Barbeiro.h"
#include <iostream>
using namespace std;

bool Barbeiro::estaDisponivel(int horario){
    for(int i=0;i<agendamentos.size();i++){
        if(horario == agendamentos[i].horario){
            return false;
        }
    }
    return true;
}