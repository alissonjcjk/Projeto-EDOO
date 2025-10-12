#pragma once
#include "Cliente.h"
#include <iostream>

using namespace std;


Cliente::Cliente(string nome, string email):Pessoa(nome, email){
    contQTDHistorico=0;
};

void Cliente::setHistorico(int dia, string servico){
    histori[contQTDHistorico].dia = dia;
    histori[contQTDHistorico].servico = servico;
    contQTDHistorico++;
}

historico* Cliente::getHistorico(){
    return histori;
}
 