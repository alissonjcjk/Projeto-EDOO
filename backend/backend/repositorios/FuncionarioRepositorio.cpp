#include "FuncionarioRepositorio.h"
#include <sstream>
#include <iostream>

FuncionarioRepositorio::FuncionarioRepositorio(Database& database)
    : db(database) {}

std::string FuncionarioRepositorio::escape(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
        if (c == '\'') out += "''";
        else out += c;
    }
    return out;
}

int FuncionarioRepositorio::deletarFuncionario(int id) {
    try {
        std::ostringstream ss;

        ss << "DELETE FROM Barbeiro WHERE id = " << id << ";";
        db.execute(ss.str());

        ss.str("");
        ss << "DELETE FROM Gestor WHERE id = " << id << ";";
        db.execute(ss.str());

        ss.str("");
        ss << "DELETE FROM Funcionario WHERE id = " << id << ";";
        if (!db.execute(ss.str())) {
            std::cerr << "Erro ao deletar da tabela Funcionario." << std::endl;
            return -1;
        }

        ss.str("");
        ss << "DELETE FROM Pessoa WHERE id = " << id << ";";
        if (!db.execute(ss.str())) {
            std::cerr << "Erro ao deletar da tabela Pessoa." << std::endl;
            return -1;
        }

        return 1; 
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao deletar funcionario: " << e.what() << std::endl;
        return -1;
    }
}

bool FuncionarioRepositorio::aumentarSalario(int funcionarioId, double valor) {
    try {
        std::ostringstream ss;
        ss << "UPDATE Funcionario SET salario = salario + " << valor
            << " WHERE id = " << funcionarioId << ";";
        return db.execute(ss.str());
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao aumentar salário: " << e.what() << std::endl;
        return false;
    }
}

Funcionario FuncionarioRepositorio::buscarPor(int id) {
    Funcionario resultado;

    auto callback = [](void* data, int argc, char** argv, char** colNames) -> int {
        auto* pFuncionario = static_cast<Funcionario*>(data);

        int id = 0;
        std::string nome, email, telefone;
        float salario = 0.0f;

        for (int i = 0; i < argc; ++i) {
            std::string col = colNames[i];
            if (col == "id" && argv[i]) id = std::stoi(argv[i]);
            else if (col == "nome" && argv[i]) nome = argv[i];
            else if (col == "email" && argv[i]) email = argv[i];
            else if (col == "telefone" && argv[i]) telefone = argv[i];
            else if (col == "salario" && argv[i]) salario = std::stof(argv[i]);
        }

        *pFuncionario = Funcionario(id, nome, email, telefone, salario);
        return 0;
    };

    std::ostringstream ss;
    ss << "SELECT p.id, p.nome, p.email, p.telefone, f.salario "
        << "FROM Pessoa p "
        << "INNER JOIN Funcionario f ON p.id = f.id "
        << "WHERE p.id = " << id << ";";

    if (!db.query(ss.str(), callback, &resultado)) {
        std::cerr << "Erro ao buscar funcionário pelo ID." << std::endl;
    }

    return resultado;
}

