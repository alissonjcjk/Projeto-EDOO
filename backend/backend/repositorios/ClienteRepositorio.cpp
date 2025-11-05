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

int ClienteRepositorio::criar(Cliente cliente, int servicoPreferidoId) {
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
        ss2 << "INSERT INTO Cliente (id, servico_preferido) VALUES (" << id << ", "<< servicoPreferidoId <<");";
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
        int servicoId = 0;
        std::string servicoNome;
        double servicoPreco = 0.0;
        int servicoDuracao = 0;

        for (int i = 0; i < argc; ++i) {
            std::string col = colNames[i];
            if (col == "id" && argv[i]) id = std::stoi(argv[i]);
            else if (col == "nome" && argv[i]) nome = argv[i];
            else if (col == "email" && argv[i]) email = argv[i];
            else if (col == "telefone" && argv[i]) telefone = argv[i];
            else if (col == "servico_id" && argv[i]) servicoId = std::stoi(argv[i]);
            else if (col == "servico_nome" && argv[i]) servicoNome = argv[i];
            else if (col == "servico_preco" && argv[i]) servicoPreco = std::stod(argv[i]);
            else if (col == "servico_duracao" && argv[i]) servicoDuracao = std::stoi(argv[i]);
        }

        Servicos s(servicoId, servicoNome, servicoPreco, servicoDuracao);
        *pCliente = Cliente(id, nome, email, telefone, s);

        return 0;
    };

    std::ostringstream ss;
    ss << "SELECT p.id, p.nome, p.email, p.telefone, "
        << "s.id AS servico_id, s.nome AS servico_nome, s.preco AS servico_preco, s.duracaoEmMinutos AS servico_duracao "
        << "FROM Pessoa p "
        << "INNER JOIN Cliente c ON p.id = c.id "
        << "INNER JOIN Servico s ON c.servico_preferido = s.id "
        << "WHERE p.id = " << id << ";";

    if (!db.query(ss.str(), callback, &resultado)) {
        std::cerr << "Erro ao buscar cliente pelo ID." << std::endl;
    }

    return resultado;
}

std::vector<Cliente> ClienteRepositorio::findAllClientes() {
    std::vector<Cliente> clientes;

    auto callback = [](void* data, int argc, char** argv, char** colNames) -> int {
        auto* pClientes = static_cast<std::vector<Cliente>*>(data);

        int id = 0;
        std::string nome, email, telefone;
        int servicoId = 0;
        std::string servicoNome;
        double servicoPreco = 0.0;
        int servicoDuracao = 0;

        for (int i = 0; i < argc; ++i) {
            std::string col = colNames[i];
            if (col == "id" && argv[i]) id = std::stoi(argv[i]);
            else if (col == "nome" && argv[i]) nome = argv[i];
            else if (col == "email" && argv[i]) email = argv[i];
            else if (col == "telefone" && argv[i]) telefone = argv[i];
            else if (col == "servico_id" && argv[i]) servicoId = std::stoi(argv[i]);
            else if (col == "servico_nome" && argv[i]) servicoNome = argv[i];
            else if (col == "servico_preco" && argv[i]) servicoPreco = std::stod(argv[i]);
            else if (col == "servico_duracao" && argv[i]) servicoDuracao = std::stoi(argv[i]);
        }

        Servicos s(servicoId, servicoNome, servicoPreco, servicoDuracao);
        pClientes->emplace_back(id, nome, email, telefone, s);

        return 0;
    };

    std::string sql = R"(
        SELECT p.id, p.nome, p.email, p.telefone,
               s.id AS servico_id, s.nome AS servico_nome, s.preco AS servico_preco, s.duracao AS servico_duracao
        FROM Pessoa p
        INNER JOIN Cliente c ON p.id = c.id
        INNER JOIN Servico s ON c.servico_preferido = s.id;
    )";

    if (!db.query(sql, callback, &clientes)) {
        std::cerr << "Erro ao buscar clientes." << std::endl;
    }

    return clientes;
}

int ClienteRepositorio::deletar(int clienteId) {
    try {
        std::ostringstream ssCliente;
        ssCliente << "DELETE FROM Cliente WHERE id = " << clienteId << ";";
        if (!db.execute(ssCliente.str())) {
            std::cerr << "Erro ao deletar cliente na tabela Cliente." << std::endl;
            return -1;
        }

        std::ostringstream ssPessoa;
        ssPessoa << "DELETE FROM Pessoa WHERE id = " << clienteId << ";";
        if (!db.execute(ssPessoa.str())) {
            std::cerr << "Erro ao deletar cliente na tabela Pessoa." << std::endl;
            return -1;
        }

        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao deletar cliente: " << e.what() << std::endl;
        return -1;
    }
}
