#include "PessoaServico.h"

PessoaServico::PessoaServico(PessoaRepositorio& repositorio) : repo(repositorio) {}

int PessoaServico::mudarNome(int id, const std::string& novoNome) {
    return repo.mudarNome(id, novoNome);
}

int PessoaServico::mudarTelefone(int id, const std::string& novoTelefone) {
    return repo.mudarTelefone(id, novoTelefone);
}
