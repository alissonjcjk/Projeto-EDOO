#pragma once
#include "Pessoa.h"
#include <iostream>

using namespace std;

/// uma struct para guardar o servico agendado e o dia em que foi agendado
struct agendamento
{
    string servico = "";
    int dia = 0;
};


class Cliente:public Pessoa{
        private:
            string servicoPreferido;
            //vetor de agendamentos, caso tenha mais de um servico disponibilizado
            agendamento agend[10];
        public:
            void setServicoPreferido(string servico);
};