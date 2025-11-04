#include "BarbeiroRepositorio.h"
#include <sstream>
#include <iostream>
#include <sqlite3.h>

BarbeiroRepository::BarbeiroRepository(Database& database) : db(database) {}

std::string BarbeiroRepository::escape(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
        if (c == '\'') out += "''"; 
        else out += c;
    }
    return out;
}

int BarbeiroRepository::createBarbeiro(Barbeiro barbeiro) {
    try {
        std::string sqlPessoa = "INSERT INTO Pessoa (nome, email, telefone) VALUES ('" +
            escape(barbeiro.getNome()) + "', '" + escape(barbeiro.getEmail()) + "', '" + escape(barbeiro.getTelefone()) + "');";

        if (!db.execute(sqlPessoa)) {
            std::cerr << "Erro ao inserir em Pessoa." << std::endl;
            return -1;
        }

        int id = -1;
        auto callback = [](void* data, int argc, char** argv, char** colNames) -> int {
            if (argc > 0 && argv[0]) {
                *(int*)data = std::stoi(argv[0]);
            }
            return 0;
        };
        db.query("SELECT last_insert_rowid();", callback, &id);
        if (id <= 0) {
            std::cerr << "Erro ao recuperar ID gerado." << std::endl;
            return -1;
        }

        std::ostringstream ss;
        ss << "INSERT INTO Funcionario (id, salario) VALUES (" << id << ", " << barbeiro.getSalario() << ");";
        if (!db.execute(ss.str())) {
            std::cerr << "Erro ao inserir em Funcionario." << std::endl;
            return -1;
        }

        std::ostringstream ss2;
        ss2 << "INSERT INTO Barbeiro (id) VALUES (" << id << ");";
        if (!db.execute(ss2.str())) {
            std::cerr << "Erro ao inserir em Barbeiro." << std::endl;
            return -1;
        }

        return id;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return -1;
    }
}

Barbeiro BarbeiroRepository::buscarPorId(int id) {
    Barbeiro resultado;

    auto callback = [](void* data, int argc, char** argv, char** colNames) -> int {
        auto* pBarbeiro = static_cast<Barbeiro*>(data);

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

        *pBarbeiro = Barbeiro(id, nome, email, telefone, salario);
        return 0;
    };

    std::ostringstream ss;
    ss << "SELECT p.id, p.nome, p.email, p.telefone, f.salario "
        << "FROM Pessoa p "
        << "INNER JOIN Funcionario f ON p.id = f.id "
        << "INNER JOIN Barbeiro b ON f.id = b.id "
        << "WHERE p.id = " << id << ";";

    if (!db.query(ss.str(), callback, &resultado)) {
        std::cerr << "Erro ao buscar barbeiro pelo ID." << std::endl;
    }

    return resultado;
}

std::vector<Barbeiro> BarbeiroRepository::findAllBarbeiros() {
    std::vector<Barbeiro> barbeiros;

    auto callback = [](void* data, int argc, char** argv, char** colNames) -> int {
        auto* pGestores = static_cast<std::vector<Barbeiro>*>(data);

        int id = 0;
        std::string nome, email, telefone;
        float salario = 0.0f;

        for (int i = 0; i < argc; i++) {
            std::string col = colNames[i];
            if (col == std::string("id") && argv[i]) id = std::stoi(argv[i]);
            else if (col == "nome" && argv[i]) nome = argv[i];
            else if (col == "email" && argv[i]) email = argv[i];
            else if (col == "telefone" && argv[i]) telefone = argv[i];
            else if (col == "salario" && argv[i]) salario = std::stof(argv[i]);
        }

        pGestores->emplace_back(id, nome, email, telefone, salario);
        return 0;
    };

    std::string sql = R"(
        SELECT p.id, p.nome, p.email, p.telefone, f.salario
        FROM Pessoa p
        INNER JOIN Funcionario f ON p.id = f.id
        INNER JOIN Barbeiro b ON f.id = b.id;
    )";

    if (!db.query(sql, callback, &barbeiros)) {
        std::cerr << "Erro ao buscar barbeiros." << std::endl;
    }

    return barbeiros;
}
