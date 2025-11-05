#pragma once
#include "../Database.h"
#include "../modelos/Funcionario.h"
#include <string>
#include <vector>

class FuncionarioRepositorio {
private:
    Database& db;
    static std::string escape(const std::string& s);

public:
    FuncionarioRepositorio(Database& database);

    int deletarFuncionario(int id);
    bool aumentarSalario(int funcionarioId, double valor);
    Funcionario buscarPor(int id);
};
