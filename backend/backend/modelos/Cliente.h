#pragma once

#include "Pessoa.h"
#include <string>
#include <vector>
#include "Servico.h"

using std::string;
using std::vector;


class Cliente : public Pessoa {
private:
    vector<string> agendamentos;
    Servicos servicoPreferido;

public:
    Cliente(int id, const std::string& nome, const std::string& email,
        const std::string& telefone, const Servicos& servicoPreferido);

    Cliente(const std::string& nome, const std::string& email,
        const std::string& telefone, const Servicos& servicoPreferido);
    Cliente();

    void setServicoPreferido(const string& servico);

    std::string getServicoPreferidoNome() const;
};
