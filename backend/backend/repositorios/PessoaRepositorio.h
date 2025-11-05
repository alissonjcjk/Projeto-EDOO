#pragma once
#include "../Database.h"
#include "../modelos/Pessoa.h"
#include <string>

class PessoaRepositorio {
private:
    Database& db;
    static std::string escape(const std::string& s);

public:
    PessoaRepositorio(Database& database);

    Pessoa buscarPorId(int id);
    int mudarNome(int id, const std::string& novoNome);
    int mudarTelefone(int id, const std::string& novoTelefone);
};