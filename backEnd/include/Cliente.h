#pragma once
#include "Pessoa.h"
#include <iostream>

using namespace std;

struct historico
{
    string servico = "";
    int dia = 0;
};
//fazer a struct cliente


class Cliente:public Pessoa{
        private:
        //usar cliente como vetor para guardar os clientes
            int contQTDHistorico;
            historico histori[10];
        public:
            Cliente(string nome, string email);
            void setHistorico(int dia, string servico);

            historico *getHistorico();
};