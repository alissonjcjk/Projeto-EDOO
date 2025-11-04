#include "ClienteRepositorio.h"
#include <sstream>
#include <iostream>
#include <sqlite3.h>

ClienteRepositorio::ClienteRepositorio(Database& database): db(database) {}

std::string ClienteRepositorio::escape(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
        if (c == '\'') out += "''";
        else out += c;
    }
    return out;
}

int ClienteRepositorio::criar(Cliente cliente) {
    try {
        std::string sqlPessoa = "INSERT INTO Pessoa (nome, email, telefone) VALUES ('" +
            escape(cliente.getNome()) + "', '" + escape(cliente.getEmail()) + "', '" + escape(cliente.getTelefone()) + "');";

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

        std::ostringstream ss2;
        ss2 << "INSERT INTO Cliente (id, servico_preferido) VALUES (" << id << ", "<< cliente.getServicoPreferido() <<");";
        if (!db.execute(ss2.str())) {
            std::cerr << "Erro ao inserir em Cliente." << std::endl;
            return -1;
        }

        return id;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return -1;
    }
}

Cliente ClienteRepositorio::buscarPorId(int id) {
    Cliente resultado;

    auto callback = [](void* data, int argc, char** argv, char** colNames) -> int {
        auto* pCliente = static_cast<Cliente*>(data);

        int id = 0;
        std::string nome, email, telefone;
        int servicoPreferido = 0;

        for (int i = 0; i < argc; ++i) {
            std::string col = colNames[i];
            if (col == "id" && argv[i]) id = std::stoi(argv[i]);
            else if (col == "nome" && argv[i]) nome = argv[i];
            else if (col == "email" && argv[i]) email = argv[i];
            else if (col == "telefone" && argv[i]) telefone = argv[i];
            else if (col == "servico_preferido" && argv[i]) servicoPreferido = std::stof(argv[i]);
        }

        *pCliente = Cliente(id, nome, email, telefone, servicoPreferido);
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

std::vector<Cliente> ClienteRepositorio::findAllClientes() {
    std::vector<Cliente> clientes;

    auto callback = [](void* data, int argc, char** argv, char** colNames) -> int {
        auto* pGestores = static_cast<std::vector<Cliente>*>(data);

        int id = 0;
        std::string nome, email, telefone;
        int servicoPreferido = 0;

        for (int i = 0; i < argc; i++) {
            std::string col = colNames[i];
            if (col == std::string("id") && argv[i]) id = std::stoi(argv[i]);
            else if (col == "nome" && argv[i]) nome = argv[i];
            else if (col == "email" && argv[i]) email = argv[i];
            else if (col == "telefone" && argv[i]) telefone = argv[i];
            else if (col == "servico_preferido" && argv[i]) servicoPreferido = std::stof(argv[i]);
        }

        pGestores->emplace_back(id, nome, email, telefone, servicoPreferido);
        return 0;
    };

    std::string sql = R"(
        SELECT p.id, p.nome, p.email, p.telefone, f.salario
        FROM Pessoa p
        INNER JOIN Funcionario f ON p.id = f.id
        INNER JOIN Cliente c ON f.id = c.id;
    )";

    if (!db.query(sql, callback, &clientes)) {
        std::cerr << "Erro ao buscar clientes." << std::endl;
    }

    return clientes;
}
