#pragma once
#include "Pessoa.h"
#include <string>
#include <vector>

// Qualquer dúvida ler a classe pai

class Cliente : public Pessoa {
    private:
        vector<string> agendamentos;
        string servicoPreferido;
    
    public:
        Cliente(int id, const string& nome, const string& email, const string& telefone, const string& servicoPreferido);
        
        void setServicoPreferido(const string& servico);
        
        string getServicoPreferido() const;
};



