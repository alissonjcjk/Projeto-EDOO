#pragma once

#include "Pessoa.h"
#include <string>
#include <vector>

using std::string;
using std::vector;


class Cliente : public Pessoa {
private:
    vector<string> agendamentos;
    int servicoPreferido;

public:
    Cliente(int id, const string& nome, const string& email, const string& telefone, const int servicoPreferido);
    Cliente(const string& nome, const string& email, const string& telefone, const int servicoPreferido);
    Cliente();

    void setServicoPreferido(const string& servico);

    int getServicoPreferido() const;
};
