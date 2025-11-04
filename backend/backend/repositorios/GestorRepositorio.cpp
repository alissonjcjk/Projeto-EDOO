#include "GestorRepositorio.h"
#include "../modelos/Gestor.h"
#include <sstream>
#include <iostream>

GestorRepositorio::GestorRepositorio(Database& database) : db(database) {}

std::string GestorRepositorio::escape(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
        if (c == '\'') out += "''";
        else out += c;
    }
    return out;
}

int GestorRepositorio::criarGestor(Gestor& gestor) {
    try {
        std::string sqlPessoa = "INSERT INTO Pessoa (nome, email, telefone) VALUES ('" +
            escape(gestor.getNome()) + "', '" + escape(gestor.getEmail()) + "', '" + escape(gestor.getTelefone()) + "');";

        if (!db.execute(sqlPessoa)) return -1;

        int id = 0;
        auto callback = [](void* data, int argc, char** argv, char** colNames) -> int {
            int* pid = static_cast<int*>(data);
            if (argc > 0 && argv[0]) *pid = std::stoi(argv[0]);
            return 0;
        };
        if (!db.query("SELECT last_insert_rowid();", callback, &id)) return -1;

        std::ostringstream ssFunc;
        ssFunc << "INSERT INTO Funcionario (id, salario) VALUES (" << id << ", " << gestor.getSalario() << ");";
        if (!db.execute(ssFunc.str())) return -1;

        std::ostringstream ssGestor;
        ssGestor << "INSERT INTO Gestor (id) VALUES (" << id << ");";
        if (!db.execute(ssGestor.str())) return -1;

        return id;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao criar gestor: " << e.what() << std::endl;
        return -1;
    }
}


std::vector<Gestor> GestorRepositorio::findAllGestores() {
    std::vector<Gestor> gestores;

    auto callback = [](void* data, int argc, char** argv, char** colNames) -> int {
        auto* pGestores = static_cast<std::vector<Gestor>*>(data);

        int id = 0;
        std::string nome, email, telefone;
        float salario = 0.0f;

        for (int i = 0; i < argc; ++i) {
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
        INNER JOIN Gestor g ON f.id = g.id;
    )";

    if (!db.query(sql, callback, &gestores)) {
        std::cerr << "Erro ao buscar gestores." << std::endl;
    }

    return gestores;
}
