#include "ApiServer.h"
#include <iostream>
#include <cpprest/http_msg.h>

using namespace web;
using namespace http;

ApiServer::ApiServer(const utility::string_t& url, const std::string& dbName)
    : listener(url), db(dbName)
{
    if (db.open()) {
        initDatabase();
    }

    barbeiroRepo = std::make_unique<BarbeiroRepository>(db);
    barbeiroService = std::make_unique<BarbeiroService>(*barbeiroRepo);
    barbeiroController = std::make_unique<BarbeiroController>(*barbeiroService);
    gestorRepo = std::make_unique<GestorRepositorio>(db);
    gestorService = std::make_unique<GestorService>(*gestorRepo);
    gestorController = std::make_unique<GestorController>(*gestorService);
    clienteRepo = std::make_unique<ClienteRepositorio>(db);
    clienteService = std::make_unique<ClienteServico>(*clienteRepo);
    clienteController = std::make_unique<ClienteControlador>(*clienteService);
    servicoRepo = std::make_unique<ServicoRepositorio>(db);
    servicoService = std::make_unique<ServicoServico>(*servicoRepo);
    servicoController = std::make_unique<ServicoControlador>(*servicoService);
    agendamentoRepo = std::make_unique<AgendamentoRepositorio>(db);
    agendamentoService = std::make_unique<AgendamentoServico>(*agendamentoRepo);
    agendamentoController = std::make_unique<AgendamentoControlador>(*agendamentoService);
    funcionarioRepo = std::make_unique<FuncionarioRepositorio>(db);
    funcionarioService = std::make_unique<FuncionarioServico>(*funcionarioRepo);
    funcionarioController = std::make_unique<FuncionarioControlador>(*funcionarioService);
    pessoaRepo = std::make_unique<PessoaRepositorio>(db);
    pessoaService = std::make_unique<PessoaServico>(*pessoaRepo);
    pessoaController = std::make_unique<PessoaControlador>(*pessoaService);

    listener.support(methods::GET, std::bind(&ApiServer::handle_request, this, std::placeholders::_1));
    listener.support(methods::POST, std::bind(&ApiServer::handle_request, this, std::placeholders::_1));
    listener.support(methods::PUT, std::bind(&ApiServer::handle_request, this, std::placeholders::_1));
    listener.support(methods::DEL, std::bind(&ApiServer::handle_request, this, std::placeholders::_1));
}

ApiServer::~ApiServer() {
    db.close();
}

Database& ApiServer::getDatabase() {
    return db;
}

void ApiServer::initDatabase() {
    db.execute("PRAGMA foreign_keys = ON;");

    db.execute("CREATE TABLE IF NOT EXISTS Pessoa (id INTEGER PRIMARY KEY AUTOINCREMENT, nome TEXT, email TEXT, telefone TEXT);");
    db.execute("CREATE TABLE IF NOT EXISTS Funcionario (id INTEGER PRIMARY KEY, salario REAL, FOREIGN KEY (id) REFERENCES Pessoa(id));");
    db.execute("CREATE TABLE IF NOT EXISTS Barbeiro (id INTEGER PRIMARY KEY, FOREIGN KEY (id) REFERENCES Funcionario(id));");
    db.execute("CREATE TABLE IF NOT EXISTS Gestor (id INTEGER PRIMARY KEY, FOREIGN KEY (id) REFERENCES Funcionario(id));");
    db.execute("CREATE TABLE IF NOT EXISTS Servico (id INTEGER PRIMARY KEY AUTOINCREMENT, nome TEXT, preco REAL, duracao INTEGER);");
    db.execute("CREATE TABLE IF NOT EXISTS Cliente (id INTEGER PRIMARY KEY, servico_preferido INTEGER, FOREIGN KEY (id) REFERENCES Pessoa(id), FOREIGN KEY (servico_preferido) REFERENCES Servico(id));");
    db.execute("CREATE TABLE IF NOT EXISTS Agendamento (id INTEGER PRIMARY KEY AUTOINCREMENT, servico INTEGER, barbeiro INTEGER, horario_inicio TEXT, horario_fim TEXT, status_agendamento TEXT, cliente INTEGER, FOREIGN KEY (servico) REFERENCES Servico(id), FOREIGN KEY (barbeiro) REFERENCES Barbeiro(id), FOREIGN KEY (cliente) REFERENCES Cliente(id));");

    std::cout << "Banco inicializado.\n";
}

void ApiServer::handle_request(http_request request) {
    auto path = uri::split_path(uri::decode(request.relative_uri().path()));
    if (path.empty()) {
        request.reply(status_codes::OK, U("Bem-vindo à API da Barbearia!"));
        return;
    }

    std::string endpoint = utility::conversions::to_utf8string(path[0]);

    if (request.method() == methods::POST) {
        if (endpoint == "barbeiro") {
            barbeiroController->create(request);
            return;
        }
        if (endpoint == "gestor") {
            gestorController->criar(request);
            return;
        }
        if (endpoint == "cliente") {
            clienteController->criar(request);
            return;
        }
        if (endpoint == "servico") {
            servicoController->criar(request);
            return;
        }
        if (endpoint == "agendamento") {
            agendamentoController->criar(request);
            return;
        }

        request.reply(status_codes::NotFound, U("Endpoint não encontrado."));
    }

    if (request.method() == methods::PUT) {
        if (path.size() == 3 && path[0] == U("servicos") && path[2] == U("valor")) {
            servicoController->mudarValor(request);
            return;
        }

        if (path.size() == 3 && path[0] == U("servicos") && path[2] == U("duracao")) {
            servicoController->mudarDuracao(request);
            return;
        }

        if (path.size() == 3 && path[0] == U("agendamento") && path[2] == U("horario")) {
            agendamentoController->atualizarHorario(request);
            return;
        }
        if (path.size() == 3 && path[0] == U("agendamento") && path[2] == U("barbeiro")) {
            agendamentoController->atualizarBarbeiro(request);
            return;
        }
        if (path.size() == 2 && path[0] == U("funcionario") && path[1] == U("aumentar-salario")) {
            funcionarioController->aumentarSalario(request);
            return;
        }
        if (path.size() == 2 && path[0] == U("pessoa") && path[3] == U("telefone")) {
            pessoaController->mudarTelefone(request);
            return;
        }
        if (path.size() == 2 && path[0] == U("pessoa") && path[3] == U("nome")) {
            pessoaController->mudarNome(request);
            return;
        }

        request.reply(status_codes::NotFound, U("Endpoint não encontrado."));
    }

    if (request.method() == methods::GET) {
        if (endpoint == "barbeiro") {
            barbeiroController->buscarPorId(request);
        }
        if (endpoint == "barbeiros") {
            barbeiroController->findAll(request);
        }
        if (endpoint == "gestores") {
            gestorController->listAll(request);
            return;
        }
        if (endpoint == "clientes") {
            clienteController->findAll(request);
            return;
        }
        if (endpoint == "cliente") {
            clienteController->buscarPorId(request);
            return;
        }
        if (endpoint == "servicos") {
            servicoController->listarTodos(request);
            return;
        }
        if (endpoint == "servico") {
            servicoController->buscarPorId(request);
            return;
        }
        if (endpoint == "agendamentos") {
            agendamentoController->listarTodos(request);
            return;
        }
        if (path.size() == 3 && path[0] == U("agendamentos") && path[2] == U("barbeiro")) {
            agendamentoController->buscarPorBarbeiroId(request);
            return;
        }
        if (path.size() == 3 && path[0] == U("agendamentos") && path[2] == U("cliene")) {
            agendamentoController->buscarPorClienteId(request);
            return;
        }
        if (path.size() == 2 && path[0] == U("agendamento")) {
            agendamentoController->buscarPorId(request);
            return;
        }


        request.reply(status_codes::NotFound, U("Endpoint não encontrado."));
    }

    if (request.method() == methods::DEL) {
        if (endpoint == "funcionario") {
            funcionarioController->deletar(request);
            return;
        }
        if (endpoint == "cliente") {
            clienteController->deletar(request);
            return;
        }
        if (endpoint == "agendamento") {
            agendamentoController->deletarAgendamento(request);
            return;
        }

        request.reply(status_codes::NotFound, U("Endpoint não encontrado."));
    }

    request.reply(status_codes::NotFound, U("Endpoint não encontrado."));
}

void ApiServer::start() {
    listener.open().wait();
    std::cout << "Servidor iniciado em: "
        << utility::conversions::to_utf8string(listener.uri().to_string())
        << std::endl;
}
