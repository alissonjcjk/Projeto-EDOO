#pragma once
#include "../repositorios/PessoaRepositorio.h"
#include "../modelos/Pessoa.h"
#include <string>

class PessoaServico {
private:
    PessoaRepositorio& repo;

public:
    PessoaServico(PessoaRepositorio& repositorio);

    int mudarNome(int id, const std::string& novoNome);
    int mudarTelefone(int id, const std::string& novoTelefone);
};
