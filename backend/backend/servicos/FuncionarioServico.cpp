#include "FuncionarioServico.h"

FuncionarioServico::FuncionarioServico(FuncionarioRepositorio& r)
    : repo(r) {}

int FuncionarioServico::deletarFuncionario(int id) {
    return repo.deletarFuncionario(id);
}

bool FuncionarioServico::aumentarSalario(int funcionarioId, double valor) {
    Funcionario funcionario = repo.buscarPor(funcionarioId);
    if (funcionario.getSalario() < valor) {
        return repo.aumentarSalario(funcionarioId, valor);
    }
    return false;
}
    
