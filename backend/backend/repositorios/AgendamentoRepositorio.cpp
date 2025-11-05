#include "AgendamentoRepositorio.h"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>

using namespace std;

AgendamentoRepositorio::AgendamentoRepositorio(Database& database)
    : db(database) {}


string AgendamentoRepositorio::escape(const string& s) {
    string result;
    for (char c : s) {
        if (c == '\'') result += "''";
        else result += c;
    }
    return result;
}

string AgendamentoRepositorio::tmParaString(const std::tm& t) {
    stringstream ss;
    ss << put_time(&t, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::tm stringParaTm(const std::string& str) {
    std::tm t = {};
    std::istringstream ss(str);
    ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S");
    return t;
}

Agendamento AgendamentoRepositorio::buscarPor(int id) {
    Agendamento ag;

    std::string sql = R"(
        SELECT 
            a.id, 
            a.horario_inicio, 
            a.horario_fim, 
            a.status_agendamento,

            b.id AS barbeiro_id,
            p_b.nome AS barbeiro_nome,
            p_b.email AS barbeiro_email,
            p_b.telefone AS barbeiro_telefone,
            f_b.salario AS barbeiro_salario,

            c.id AS cliente_id,
            p_c.nome AS cliente_nome,
            p_c.email AS cliente_email,
            p_c.telefone AS cliente_telefone,
            c.servico_preferido,

            s.id AS servico_id,
            s.nome AS servico_nome,
            s.preco AS servico_preco,
            s.duracao AS servico_duracao

        FROM Agendamento a
        INNER JOIN Barbeiro b ON a.barbeiro = b.id
        INNER JOIN Funcionario f_b ON b.id = f_b.id
        INNER JOIN Pessoa p_b ON f_b.id = p_b.id
        INNER JOIN Cliente c ON a.cliente = c.id
        INNER JOIN Pessoa p_c ON c.id = p_c.id
        INNER JOIN Servico s ON a.servico = s.id
        WHERE a.id = )" + std::to_string(id) + ";";

    auto callback = [](void* data, int argc, char** argv, char** colNames) -> int {
        if (argc < 18) return 0;

        std::tm inicio = argv[1] ? stringParaTm(argv[1]) : std::tm{};
        std::tm fim = argv[2] ? stringParaTm(argv[2]) : std::tm{};
        bool concluido = argv[3] && std::string(argv[3]) == "CONCLUIDO";

        Barbeiro b(
            argv[4] ? std::stoi(argv[4]) : 0,
            argv[5] ? std::string(argv[5]) : "",
            argv[6] ? std::string(argv[6]) : "",
            argv[7] ? std::string(argv[7]) : "",
            argv[8] ? std::stof(argv[8]) : 0.0f
        );

        Cliente c(
            argv[9] ? std::stoi(argv[9]) : 0,
            argv[10] ? std::string(argv[10]) : "",
            argv[11] ? std::string(argv[11]) : "",
            argv[12] ? std::string(argv[12]) : "",
            Servicos{}
        );

        Servicos s(
            argv[14] ? std::stoi(argv[14]) : 0,
            argv[15] ? std::string(argv[15]) : "",
            argv[16] ? std::stod(argv[16]) : 0.0,
            argv[17] ? std::stoi(argv[17]) : 0
        );

        Agendamento ag(
            argv[0] ? std::stoi(argv[0]) : 0,
            new Cliente(c),
            new Barbeiro(b),
            new Servicos(s),
            inicio,
            fim
        );

        if (concluido)
            ag.concluir();

        return 0;
    };

    db.query(sql, callback, &ag);

    if (ag.getId() == 0) {
        throw std::runtime_error("Agendamento não encontrado.");
    }

    return ag;
}


vector<Agendamento> AgendamentoRepositorio::listarTodos() {
    vector<Agendamento> agendamentos;

    std::string sql = R"(
        SELECT 
            a.id, 
            a.horario_inicio, 
            a.horario_fim, 
            a.status_agendamento,

            b.id AS barbeiro_id,
            p_b.nome AS barbeiro_nome,
            p_b.email AS barbeiro_email,
            p_b.telefone AS barbeiro_telefone,
            f_b.salario AS barbeiro_salario,

            c.id AS cliente_id,
            p_c.nome AS cliente_nome,
            p_c.email AS cliente_email,
            p_c.telefone AS cliente_telefone,
            c.servico_preferido,

            s.id AS servico_id,
            s.nome AS servico_nome,
            s.preco AS servico_preco,
            s.duracao AS servico_duracao

        FROM Agendamento a
        INNER JOIN Barbeiro b ON a.barbeiro = b.id
        INNER JOIN Funcionario f_b ON b.id = f_b.id
        INNER JOIN Pessoa p_b ON f_b.id = p_b.id
        INNER JOIN Cliente c ON a.cliente = c.id
        INNER JOIN Pessoa p_c ON c.id = p_c.id
        INNER JOIN Servico s ON a.servico = s.id;
    )";

    auto callback = [](void* data, int argc, char** argv, char** colNames) -> int {
        vector<Agendamento>* lista = static_cast<vector<Agendamento>*>(data);

        std::tm inicio = argv[1] ? stringParaTm(argv[1]) : std::tm{};
        std::tm fim = argv[2] ? stringParaTm(argv[2]) : std::tm{};
        bool concluido = argv[3] && std::string(argv[3]) == "CONCLUIDO";

        Barbeiro barbeiro(
            argv[4] ? stoi(argv[4]) : 0,
            argv[5] ? string(argv[5]) : "",
            argv[6] ? string(argv[6]) : "",
            argv[7] ? string(argv[7]) : "",
            argv[8] ? stof(argv[8]) : 0.0f
        );

        Cliente cliente(
            argv[9] ? stoi(argv[9]) : 0,
            argv[10] ? string(argv[10]) : "",
            argv[11] ? string(argv[11]) : "",
            argv[12] ? string(argv[12]) : "",
            Servicos{}
        );

        Servicos servico(
            argv[14] ? stoi(argv[14]) : 0,
            argv[15] ? string(argv[15]) : "",
            argv[16] ? stod(argv[16]) : 0.0,
            argv[17] ? stoi(argv[17]) : 0
        );

        Agendamento agendamento(
            argv[0] ? stoi(argv[0]) : 0,
            new Cliente(cliente),
            new Barbeiro(barbeiro),
            new Servicos(servico),
            inicio,
            fim
        );

        if (concluido)
            agendamento.concluir();

        lista->push_back(agendamento);
        return 0;
    };

    db.query(sql, callback, &agendamentos);
    return agendamentos;
}

int AgendamentoRepositorio::criar(int clienteId, int barbeiroId, int servicoId,
    const std::tm& horarioInicio, const std::tm& horarioFim)
{
    try {
        std::string sql =
            "INSERT INTO Agendamento (cliente, barbeiro, servico, horario_inicio, horario_fim, status_agendamento) VALUES (" +
            std::to_string(clienteId) + ", " +
            std::to_string(barbeiroId) + ", " +
            std::to_string(servicoId) + ", '" +
            escape(tmParaString(horarioInicio)) + "', '" +
            escape(tmParaString(horarioFim)) + "', 'PENDENTE');";

        if (db.execute(sql)) {
            std::cout << "Agendamento criado com sucesso.\n";
            return 1;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao criar agendamento: " << e.what() << std::endl;
    }
    return 0;
}

vector<Agendamento> AgendamentoRepositorio::listarTodosAgendamentosPorBarbeiro(int id) {
    vector<Agendamento> agendamentos;

    std::string sql = R"(
        SELECT 
            a.id, a.horario_inicio, a.horario_fim, a.status_agendamento,
            b.id AS barbeiro_id, p_b.nome AS barbeiro_nome, p_b.email AS barbeiro_email, p_b.telefone AS barbeiro_telefone, f_b.salario AS barbeiro_salario,
            c.id AS cliente_id, p_c.nome AS cliente_nome, p_c.email AS cliente_email, p_c.telefone AS cliente_telefone, c.servico_preferido,
            s.id AS servico_id, s.nome AS servico_nome, s.preco AS servico_preco, s.duracao AS servico_duracao
        FROM Agendamento a
        INNER JOIN Barbeiro b ON a.barbeiro = b.id
        INNER JOIN Funcionario f_b ON b.id = f_b.id
        INNER JOIN Pessoa p_b ON f_b.id = p_b.id
        INNER JOIN Cliente c ON a.cliente = c.id
        INNER JOIN Pessoa p_c ON c.id = p_c.id
        INNER JOIN Servico s ON a.servico = s.id
        WHERE a.barbeiro = )" + std::to_string(id) + ";";

    db.query(sql, [](void* data, int argc, char** argv, char** colNames) -> int {
        vector<Agendamento>* lista = static_cast<vector<Agendamento>*>(data);

        std::tm inicio = argv[1] ? stringParaTm(argv[1]) : std::tm{};
        std::tm fim = argv[2] ? stringParaTm(argv[2]) : std::tm{};
        bool concluido = argv[3] && std::string(argv[3]) == "CONCLUIDO";

        Barbeiro barbeiro(
            argv[4] ? stoi(argv[4]) : 0,
            argv[5] ? string(argv[5]) : "",
            argv[6] ? string(argv[6]) : "",
            argv[7] ? string(argv[7]) : "",
            argv[8] ? stof(argv[8]) : 0.0f
        );

        Cliente cliente(
            argv[9] ? stoi(argv[9]) : 0,
            argv[10] ? string(argv[10]) : "",
            argv[11] ? string(argv[11]) : "",
            argv[12] ? string(argv[12]) : "",
            Servicos{}
        );

        Servicos servico(
            argv[14] ? stoi(argv[14]) : 0,
            argv[15] ? string(argv[15]) : "",
            argv[16] ? stod(argv[16]) : 0.0,
            argv[17] ? stoi(argv[17]) : 0
        );

        Agendamento agendamento(
            argv[0] ? stoi(argv[0]) : 0,
            new Cliente(cliente),
            new Barbeiro(barbeiro),
            new Servicos(servico),
            inicio,
            fim
        );
        if (concluido)
            agendamento.concluir();

        lista->push_back(agendamento);
        return 0;
        }, &agendamentos);

    return agendamentos;
}

vector<Agendamento> AgendamentoRepositorio::listarTodosAgendamentosPorCliente(int id) {
    vector<Agendamento> agendamentos;

    std::string sql = R"(
        SELECT 
            a.id, a.horario_inicio, a.horario_fim, a.status_agendamento,
            b.id AS barbeiro_id, p_b.nome AS barbeiro_nome, p_b.email AS barbeiro_email, p_b.telefone AS barbeiro_telefone, f_b.salario AS barbeiro_salario,
            c.id AS cliente_id, p_c.nome AS cliente_nome, p_c.email AS cliente_email, p_c.telefone AS cliente_telefone, c.servico_preferido,
            s.id AS servico_id, s.nome AS servico_nome, s.preco AS servico_preco, s.duracao AS servico_duracao
        FROM Agendamento a
        INNER JOIN Barbeiro b ON a.barbeiro = b.id
        INNER JOIN Funcionario f_b ON b.id = f_b.id
        INNER JOIN Pessoa p_b ON f_b.id = p_b.id
        INNER JOIN Cliente c ON a.cliente = c.id
        INNER JOIN Pessoa p_c ON c.id = p_c.id
        INNER JOIN Servico s ON a.servico = s.id
        WHERE a.cliente = )" + std::to_string(id) + ";";

    db.query(sql, [](void* data, int argc, char** argv, char** colNames) -> int {
        vector<Agendamento>* lista = static_cast<vector<Agendamento>*>(data);

        std::tm inicio = argv[1] ? stringParaTm(argv[1]) : std::tm{};
        std::tm fim = argv[2] ? stringParaTm(argv[2]) : std::tm{};
        bool concluido = argv[3] && std::string(argv[3]) == "CONCLUIDO";

        Barbeiro barbeiro(
            argv[4] ? stoi(argv[4]) : 0,
            argv[5] ? string(argv[5]) : "",
            argv[6] ? string(argv[6]) : "",
            argv[7] ? string(argv[7]) : "",
            argv[8] ? stof(argv[8]) : 0.0f
        );

        Cliente cliente(
            argv[9] ? stoi(argv[9]) : 0,
            argv[10] ? string(argv[10]) : "",
            argv[11] ? string(argv[11]) : "",
            argv[12] ? string(argv[12]) : "",
            Servicos{}
        );

        Servicos servico(
            argv[14] ? stoi(argv[14]) : 0,
            argv[15] ? string(argv[15]) : "",
            argv[16] ? stod(argv[16]) : 0.0,
            argv[17] ? stoi(argv[17]) : 0
        );

        Agendamento agendamento(
            argv[0] ? stoi(argv[0]) : 0,
            new Cliente(cliente),
            new Barbeiro(barbeiro),
            new Servicos(servico),
            inicio,
            fim
        );
        if (concluido)
            agendamento.concluir();

        lista->push_back(agendamento);
        return 0;
        }, &agendamentos);

    return agendamentos;
}


int AgendamentoRepositorio::mudarBarbeiroResponsavel(int novoBarbeiroId, int agendamentoId) {
    string sql = "UPDATE Agendamento SET barbeiro = " + to_string(novoBarbeiroId) +
        " WHERE id = " + to_string(agendamentoId) + ";";
    return db.execute(sql) ? 1 : 0;
}

int AgendamentoRepositorio::mudarData(std::tm horarioInicio, std::tm horarioFim, int agendamentoId) {
    string sql = "UPDATE Agendamento SET horario_inicio = '" + escape(tmParaString(horarioInicio)) +
        "', horario_fim = '" + escape(tmParaString(horarioFim)) +
        "' WHERE id = " + to_string(agendamentoId) + ";";
    return db.execute(sql) ? 1 : 0;
}

int AgendamentoRepositorio::deletarAgendamento(int agendamentoId) {
    string sql = "DELETE FROM Agendamento WHERE id = " + to_string(agendamentoId) + ";";
    return db.execute(sql) ? 1 : 0;
}
