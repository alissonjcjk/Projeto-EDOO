#pragma once
#include "Pessoa.h"
#include <vector>

class Cliente : public Pessoa {

    private:
        bool membroClube;
        vector<string> historicoServicos;
    public:
        Cliente(string n, string e, bool membro=false) :
        Pessoa(n, e), membroClube(membro) {};

        void setHistorico(string servico);
        void getHistorico();
        
};