#pragma once
#include "Pessoa.h"
#include <string>
#include <vector>
#include "Agendamento.h"

// Qualquer dúvida ler a classe pai

class Cliente : public Pessoa {
    private:
        vector<string> agendamentos;
        string servicoPreferido;
        Agendamento agendamento;
    public:
        Cliente(int id, const string& nome, const string& email, const string& telefone, const string& servicoPreferido);

        void setAgendamento(int id, Cliente* cliente, Barbeiro* barbeiro, Servico* servico, const string& data, const string& horarioInicio, const string& horarioFim);

        
        void setServicoPreferido(const string& servico);
        
        string getServicoPreferido() const;
};



