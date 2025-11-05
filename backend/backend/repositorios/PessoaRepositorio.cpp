#include "PessoaRepositorio.h"
#include <sstream>
#include <iostream>

PessoaRepositorio::PessoaRepositorio(Database& database) : db(database) {}

std::string PessoaRepositorio::escape(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
        if (c == '\'') out += "''";
        else out += c;
    }
    return out;
}

Pessoa PessoaRepositorio::buscarPorId(int id) {
    Pessoa resultado;

    auto callback = [](void* data, int argc, char** argv, char** colNames) -> int {
        auto* pPessoa = static_cast<Pessoa*>(data);

        int id = 0;
        std::string nome, email, telefone;

        for (int i = 0; i < argc; ++i) {
            std::string col = colNames[i];
            if (col == "id" && argv[i]) id = std::stoi(argv[i]);
            else if (col == "nome" && argv[i]) nome = argv[i];
            else if (col == "email" && argv[i]) email = argv[i];
            else if (col == "telefone" && argv[i]) telefone = argv[i];
        }

        *pPessoa = Pessoa(id, nome, email, telefone);
        return 0;
    };

    std::ostringstream ss;
    ss << "SELECT id, nome, email, telefone FROM Pessoa WHERE id = " << id << ";";

    if (!db.query(ss.str(), callback, &resultado)) {
        std::cerr << "Erro ao buscar pessoa pelo ID." << std::endl;
    }

    return resultado;
}

int PessoaRepositorio::mudarNome(int id, const std::string& novoNome) {
    std::ostringstream ss;
    ss << "UPDATE Pessoa SET nome = '" << escape(novoNome) << "' WHERE id = " << id << ";";
    return db.execute(ss.str()) ? 1 : -1;
}

int PessoaRepositorio::mudarTelefone(int id, const std::string& novoTelefone) {
    std::ostringstream ss;
    ss << "UPDATE Pessoa SET telefone = '" << escape(novoTelefone) << "' WHERE id = " << id << ";";
    return db.execute(ss.str()) ? 1 : -1;
}
