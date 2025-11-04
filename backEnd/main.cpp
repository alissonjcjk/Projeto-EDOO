#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Cliente.h"
#include "Barbeiro.h"
#include "Servico.h"
#include "Agendamento.h"
#include "Gestor.h"
#include "ArquivoManager.h"
#include "httplib.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;
using namespace httplib;

// Funções auxiliares para converter objetos para JSON
json clienteToJson(const Cliente& cliente) {
    return {
        {"id", cliente.getId()},
        {"name", cliente.getNome()},
        {"email", cliente.getEmail()},
        {"phone", cliente.getTelefone()},
        {"preferredService", cliente.getServicoPreferido()}
    };
}

json barbeiroToJson(const Barbeiro& barbeiro) {
    return {
        {"id", barbeiro.getId()},
        {"name", barbeiro.getNome()},
        {"email", barbeiro.getEmail()},
        {"phone", barbeiro.getTelefone()},
        {"specialty", barbeiro.getEspecialidade()},
        {"startTime", "09:00"},
        {"endTime", "18:00"},
        {"salary", "R$ 3300,00"}
    };
}

json servicoToJson(const Servico& servico) {
    return {
        {"id", servico.getId()},
        {"name", servico.getNome()},
        {"price", servico.getPreco()},
        {"duration", servico.getDuracao()}
    };
}

json agendamentoToJson(const Agendamento& agendamento) {
    return {
        {"id", agendamento.getId()},
        {"clientId", agendamento.getCliente()->getId()},
        {"barberId", agendamento.getBarbeiro()->getId()},
        {"serviceId", agendamento.getServico()->getId()},
        {"date", agendamento.getData()},
        {"time", agendamento.gethorarioInicio()},
        {"status", "agendado"} // Você pode adicionar status no seu modelo
    };
}


// Função para configurar headers CORS
void set_cors_headers(Response& res) {
    res.set_header("Access-Control-Allow-Origin", "http://localhost:5173");
    res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
    res.set_header("Access-Control-Max-Age", "86400");
}

int main() {
    vector<Cliente> clientes;
    vector<Barbeiro> barbeiros;
    vector<Servico> servicos;
    vector<Agendamento> agendamentos;
    vector<Gestor> gestores;

    // Carregar dados dos arquivos
    ArquivoManager::carregarClientes(clientes);
    ArquivoManager::carregarBarbeiros(barbeiros);
    ArquivoManager::carregarServicos(servicos);
    ArquivoManager::carregarAgendamentos(agendamentos);

    // Inicializar IDs
    int idAgendamentoCliente = ArquivoManager::obterUltimoIdCliente();
    int idAgendamentoBarbeiro = ArquivoManager::obterUltimoIdBarbeiro();
    int idAgendamento = ArquivoManager::obterUltimoIdAgendamento();
    int idCadastroServico = ArquivoManager::obterUltimoIdServico();

    Server svr;

    // REMOVA esta linha que causa duplicação:
    // svr.set_default_headers({...});

    // Rota para obter clientes
    svr.Get("/api/clients", [&](const Request& req, Response& res) {
        set_cors_headers(res);
        json clientsJson = json::array();
        for (const auto& cliente : clientes) {
            clientsJson.push_back(clienteToJson(cliente));
        }
        res.set_content(clientsJson.dump(), "application/json");
    });

    // Rota para criar cliente
    svr.Post("/api/clients", [&](const Request& req, Response& res) {
        set_cors_headers(res);
        
        try {
            auto body = json::parse(req.body);
            
            string nome = body["name"];
            string email = body["email"];
            string telefone = body["phone"];
            string servicoPrefe = body.value("preferredService", "");
            
            Cliente novoCliente(idAgendamentoCliente, nome, email, telefone, servicoPrefe);
            clientes.push_back(novoCliente);
            idAgendamentoCliente++;
            
            ArquivoManager::salvarClientes(clientes);
            
            json response = clienteToJson(novoCliente);
            res.set_content(response.dump(), "application/json");
        } catch (const exception& e) {
            res.status = 400;
            json error = {{"error", e.what()}};
            res.set_content(error.dump(), "application/json");
        }
    });

    // Rota para obter barbeiros
    svr.Get("/api/barbers", [&](const Request& req, Response& res) {
        set_cors_headers(res);
        json barbersJson = json::array();
        for (const auto& barbeiro : barbeiros) {
            barbersJson.push_back(barbeiroToJson(barbeiro));
        }
        res.set_content(barbersJson.dump(), "application/json");
    });

    // Rota para criar barbeiro
    svr.Post("/api/barbers", [&](const Request& req, Response& res) {
        set_cors_headers(res);
        
        try {
            auto body = json::parse(req.body);
            
            string nome = body["name"];
            string email = body["email"];
            string telefone = body["phone"];
            string especialidade = body["specialty"];
            
            Barbeiro novoBarbeiro(6, 20, idAgendamentoBarbeiro, nome, email, telefone, especialidade);
            barbeiros.push_back(novoBarbeiro);
            idAgendamentoBarbeiro++;
            
            ArquivoManager::salvarBarbeiros(barbeiros);
            
            json response = barbeiroToJson(novoBarbeiro);
            res.set_content(response.dump(), "application/json");
        } catch (const exception& e) {
            res.status = 400;
            json error = {{"error", e.what()}};
            res.set_content(error.dump(), "application/json");
        }
    });

    // Rota OPTIONS para CORS preflight
    svr.Options(R"(/api/.*)", [](const Request& req, Response& res) {
        set_cors_headers(res);
        res.status = 200;
    });

    // Rota para serviços
    svr.Get("/api/services", [&](const Request& req, Response& res) {
        set_cors_headers(res);
        json servicesJson = json::array();
        for (const auto& servico : servicos) {
            servicesJson.push_back(servicoToJson(servico));
        }
        res.set_content(servicesJson.dump(), "application/json");
    });

    // Rota para agendamentos
    svr.Post("/api/appointments", [&](const Request& req, Response& res) {
        set_cors_headers(res);
        
        try {
            auto body = json::parse(req.body);
            
            int clientId = body["clientId"];
            int barberId = body["barberId"];
            int serviceId = body["serviceId"];
            string data = body["date"];
            string time = body["time"];
            string status = body.value("status", "agendado");

            // ... (sua lógica de agendamento)
            
            json response = {{"message", "Agendamento criado com sucesso"}};
            res.set_content(response.dump(), "application/json");
        } catch (const exception& e) {
            res.status = 400;
            json error = {{"error", e.what()}};
            res.set_content(error.dump(), "application/json");
        }
    });

    cout << "Servidor rodando na porta 8080..." << endl;
    svr.listen("localhost", 8080);

    return 0;
}