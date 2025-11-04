#include "ServicoRepositorio.h"
#include <sstream>
#include <iostream>

ServicoRepositorio::ServicoRepositorio(Database& database)
    : db(database) {}

std::string ServicoRepositorio::escape(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
        if (c == '\'') out += "''";
        else out += c;
    }
    return out;
}

int ServicoRepositorio::criar(Servicos servico) {
    try {
        std::ostringstream ss;
        ss << "INSERT INTO Servico (nome, preco, duracao) VALUES ('"
            << escape(servico.getNome()) << "', "
            << servico.getPreco() << ", "
            << servico.getDuracao() << ");";

        if (!db.execute(ss.str())) {
            std::cerr << "Erro ao inserir em Servico." << std::endl;
            return -1;
        }

        
        int id = -1;
        auto callback = [](void* data, int argc, char** argv, char**) -> int {
            if (argc > 0 && argv[0]) *(int*)data = std::stoi(argv[0]);
            return 0;
        };
        db.query("SELECT last_insert_rowid();", callback, &id);
        return id;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao criar serviço: " << e.what() << std::endl;
        return -1;
    }
}


int ServicoRepositorio::mudarValor(int servicoId, double novoValor) {
    try {
        std::ostringstream ss;
        ss << "UPDATE Servico SET preco = " << novoValor
            << " WHERE id = " << servicoId << ";";
        if (!db.execute(ss.str())) {
            std::cerr << "Erro ao atualizar valor do serviço." << std::endl;
            return -1;
        }
        return servicoId;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao mudar valor: " << e.what() << std::endl;
        return -1;
    }
}


int ServicoRepositorio::mudarDuracao(int servicoId, int novaDuracao) {
    try {
        std::ostringstream ss;
        ss << "UPDATE Servico SET duracao = " << novaDuracao
            << " WHERE id = " << servicoId << ";";
        if (!db.execute(ss.str())) {
            std::cerr << "Erro ao atualizar duração do serviço." << std::endl;
            return -1;
        }
        return servicoId;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao mudar duração: " << e.what() << std::endl;
        return -1;
    }
}

Servicos ServicoRepositorio::buscarServicoPor(int id) {
    Servicos servico;

    try {
        std::ostringstream ss;
        ss << "SELECT id, nome, preco, duracao FROM Servico WHERE id = " << id << ";";

        auto callback = [](void* data, int argc, char** argv, char** colNames) -> int {
            Servicos* s = static_cast<Servicos*>(data);
            for (int i = 0; i < argc; i++) {
                std::string col = colNames[i];
                if (col == "id" && argv[i]) s->setId(std::stoi(argv[i]));
                else if (col == "nome" && argv[i]) s->setNome(argv[i]);
                else if (col == "preco" && argv[i]) s->setPreco(std::stof(argv[i]));
                else if (col == "duracao" && argv[i]) s->setDuracao(std::stoi(argv[i]));
            }
            return 0;
        };

        db.query(ss.str(), callback, &servico);
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao buscar serviço: " << e.what() << std::endl;
    }

    return servico;
}

std::vector<Servicos> ServicoRepositorio::listarTodos() {
    std::vector<Servicos> lista;

    try {
        std::string sql = "SELECT id, nome, preco, duracao FROM Servico;";

        auto callback = [](void* data, int argc, char** argv, char** colNames) -> int {
            auto* listaServicos = static_cast<std::vector<Servicos>*>(data);
            Servicos s;

            for (int i = 0; i < argc; i++) {
                std::string col = colNames[i];
                if (col == "id" && argv[i]) s.setId(std::stoi(argv[i]));
                else if (col == "nome" && argv[i]) s.setNome(argv[i]);
                else if (col == "preco" && argv[i]) s.setPreco(std::stof(argv[i]));
                else if (col == "duracao" && argv[i]) s.setDuracao(std::stoi(argv[i]));
            }

            listaServicos->push_back(s);
            return 0;
        };

        if (!db.query(sql, callback, &lista)) {
            std::cerr << "Erro ao consultar todos os serviços." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao listar serviços: " << e.what() << std::endl;
    }

    return lista;
}