#pragma once
#include "../repositorios/FuncionarioRepositorio.h"
#include "../modelos/Funcionario.h"
#include <vector>

class FuncionarioServico {
private:
    FuncionarioRepositorio& repo;

public:
    FuncionarioServico(FuncionarioRepositorio& r);

    int deletarFuncionario(int id);
    bool aumentarSalario(int funcionarioId, double valor);
};