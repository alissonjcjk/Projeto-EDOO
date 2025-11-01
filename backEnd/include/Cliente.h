#pragma once
#include "Pessoa.h"
#include <string>
#include <vector>
#include "Agendamento.h"

// Qualquer dúvida ler a classe pai
class Barbeiro;
class Cliente;
class Servico;

class Cliente : public Pessoa {
    private:
        string servicoPreferido;
    public:
        Cliente(int id, const string& nome, const string& email, const string& telefone, const string& servicoPreferido);
        
        void setServicoPreferido(const string& servico);
        
        string getServicoPreferido() const;
};



