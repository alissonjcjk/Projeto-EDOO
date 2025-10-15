#pragma once
#include "Barbeiro.h"
#include "Faxineira.h"
#include "Cliente.h"
#include <iostream>

using namespace std;


class Barbearia{
    private:
        string servicos[3];
        string horatioAtend;
        osFuncionarios funcio[10];
        string clientesEsperando[10];
        string servicosDispo[4];
    public:
        Barbearia();
        //string* getServicos();
        //void setAgendarServico();
        string getHorarioAtend();

};