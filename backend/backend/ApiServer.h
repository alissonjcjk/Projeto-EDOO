#pragma once
#include "Database.h"
#include "./controladores/BarbeiroControlador.h"
#include "./repositorios/BarbeiroRepositorio.h"
#include "./servicos/BarbeiroServico.h"
#include "./controladores/GestorControlador.h"
#include "./repositorios/GestorRepositorio.h"
#include "./servicos/GestorServico.h"
#include "./controladores/ClienteControlador.h"
#include "./repositorios/ClienteRepositorio.h"
#include "./servicos/ClienteServico.h"
#include "./controladores/ServicoControlador.h"
#include "./repositorios/ServicoRepositorio.h"
#include "./servicos/ServicoServico.h"
#include "./controladores/AgendamentoControlador.h"
#include "./repositorios/AgendamentoRepositorio.h"
#include "./servicos/AgendamentoServico.h"
#include "./controladores/FuncionarioControlador.h"
#include "./repositorios/FuncionarioRepositorio.h"
#include "./servicos/FuncionarioServico.h"
#include "./controladores/PessoaControlador.h"
#include "./repositorios/PessoaRepositorio.h"
#include "./servicos/PessoaServico.h"
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <memory>

using namespace web::http::experimental::listener;

class ApiServer {
private:
    http_listener listener;
    Database db;

    // Controllers
    std::unique_ptr<BarbeiroRepository> barbeiroRepo;
    std::unique_ptr<BarbeiroService> barbeiroService;
    std::unique_ptr<BarbeiroController> barbeiroController;
    std::unique_ptr<GestorRepositorio> gestorRepo;
    std::unique_ptr<GestorService> gestorService;
    std::unique_ptr<GestorController> gestorController;
    std::unique_ptr<ClienteRepositorio> clienteRepo;
    std::unique_ptr<ClienteServico> clienteService;
    std::unique_ptr<ClienteControlador> clienteController;
    std::unique_ptr<ServicoRepositorio> servicoRepo;
    std::unique_ptr<ServicoServico> servicoService;
    std::unique_ptr<ServicoControlador> servicoController;
    std::unique_ptr<AgendamentoRepositorio> agendamentoRepo;
    std::unique_ptr<AgendamentoServico> agendamentoService;
    std::unique_ptr<AgendamentoControlador> agendamentoController;
    std::unique_ptr<FuncionarioRepositorio> funcionarioRepo;
    std::unique_ptr<FuncionarioServico> funcionarioService;
    std::unique_ptr<FuncionarioControlador> funcionarioController;
    std::unique_ptr<PessoaRepositorio> pessoaRepo;
    std::unique_ptr<PessoaServico> pessoaService;
    std::unique_ptr<PessoaControlador> pessoaController;


public:
    ApiServer(const utility::string_t& url, const std::string& dbName);
    ~ApiServer();

    void start();
    Database& getDatabase();

private:
    void initDatabase();
    void handle_request(web::http::http_request request);
};
