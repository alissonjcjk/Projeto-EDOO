#include "AgendamentoControlador.h"
#include <sstream>
#include <iomanip>
#include <iostream>

AgendamentoControlador::AgendamentoControlador(AgendamentoServico& svc)
    : service(svc) {}

std::tm AgendamentoControlador::stringParaTm(const std::string& dataHoraStr) {
    std::tm t = {};
    std::istringstream ss(dataHoraStr);
    ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) throw std::runtime_error("Formato de data/hora inválido: " + dataHoraStr);
    return t;
}

std::string tmParaString(const std::tm& t) {
    std::stringstream ss;
    ss << std::put_time(&t, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void AgendamentoControlador::criar(http_request request) {
    request.extract_json().then([this, request](pplx::task<json::value> task) mutable {
        try {
            json::value j = task.get();

            if (!j.has_field(U("clienteId")) || !j.has_field(U("barbeiroId")) ||
                !j.has_field(U("servicoId")) || !j.has_field(U("horarioInicio")) ||
                !j.has_field(U("horarioFim"))) {
                request.reply(status_codes::BadRequest, U("Campos obrigatorios: clienteId, barbeiroId, servicoId, horarioInicio, horarioFim"));
                return;
            }

            int clienteId = j[U("clienteId")].as_integer();
            int barbeiroId = j[U("barbeiroId")].as_integer();
            int servicoId = j[U("servicoId")].as_integer();
            std::string inicioStr = utility::conversions::to_utf8string(j[U("horarioInicio")].as_string());
            std::string fimStr = utility::conversions::to_utf8string(j[U("horarioFim")].as_string());

            std::tm inicio = stringParaTm(inicioStr);
            std::tm fim = stringParaTm(fimStr);

            int id = service.criar(clienteId, barbeiroId, servicoId, inicio, fim);

            if (id <= 0) {
                request.reply(status_codes::InternalError, U("Falha ao criar agendamento"));
                return;
            }

            json::value out = json::value::object();
            out[U("id")] = json::value::number(id);
            out[U("mensagem")] = json::value::string(U("Agendamento criado com sucesso"));
            request.reply(status_codes::Created, out);
        }
        catch (const std::exception& e) {
            request.reply(status_codes::BadRequest, utility::conversions::to_string_t(e.what()));
        }
        catch (...) {
            request.reply(status_codes::InternalError, U("Erro desconhecido"));
        }
        });
}

void AgendamentoControlador::buscarPorId(http_request request) {
    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));
    if (paths.size() < 2) {
        request.reply(status_codes::BadRequest, U("ID do agendamento não informado."));
        return;
    }

    int id = std::stoi(utility::conversions::to_utf8string(paths[1]));

    try {
        Agendamento ag = service.buscaPor(id);
        if (ag.getId() == 0) {
            request.reply(status_codes::NotFound, U("Agendamento não encontrado."));
            return;
        }

        json::value out = json::value::object();
        out[U("id")] = json::value::number(ag.getId());
        out[U("concluido")] = json::value::boolean(ag.isConcluido());
        out[U("horarioInicio")] = json::value::string(utility::conversions::to_string_t(tmParaString(ag.getHorarioInicio())));
        out[U("horarioFim")] = json::value::string(utility::conversions::to_string_t(tmParaString(ag.getHorarioFim())));

        json::value barbeiroJson;
        barbeiroJson[U("id")] = json::value::number(ag.getBarbeiro()->getId());
        barbeiroJson[U("nome")] = json::value::string(utility::conversions::to_string_t(ag.getBarbeiro()->getNome()));
        out[U("barbeiro")] = barbeiroJson;

        json::value clienteJson;
        clienteJson[U("id")] = json::value::number(ag.getCliente()->getId());
        clienteJson[U("nome")] = json::value::string(utility::conversions::to_string_t(ag.getCliente()->getNome()));
        out[U("cliente")] = clienteJson;

        json::value servicoJson;
        servicoJson[U("id")] = json::value::number(ag.getServico()->getId());
        servicoJson[U("nome")] = json::value::string(utility::conversions::to_string_t(ag.getServico()->getNome()));
        out[U("servico")] = servicoJson;

        request.reply(status_codes::OK, out);
    }
    catch (const std::exception& e) {
        request.reply(status_codes::InternalError, utility::conversions::to_string_t(e.what()));
    }
}

void AgendamentoControlador::listarTodos(http_request request) {
    json::value result = json::value::array();
    auto agendamentos = service.listarTodos();
    int i = 0;
    for (auto& ag : agendamentos) {
        json::value j;
        j[U("id")] = json::value::number(ag.getId());
        j[U("concluido")] = json::value::boolean(ag.isConcluido());
        j[U("horarioInicio")] = json::value::string(utility::conversions::to_string_t(tmParaString(ag.getHorarioInicio())));
        j[U("horarioFim")] = json::value::string(utility::conversions::to_string_t(tmParaString(ag.getHorarioFim())));
        result[i++] = j;
    }
    request.reply(status_codes::OK, result);
}

void AgendamentoControlador::buscarPorBarbeiroId(http_request request) {
    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));
    if (paths.empty()) {
        request.reply(status_codes::BadRequest, U("ID do barbeiro não informado."));
        return;
    }
    int barbeiroId = std::stoi(utility::conversions::to_utf8string(paths[0]));
    auto ags = service.listarTodosPorBarbeiro(barbeiroId);

    json::value result = json::value::array();
    int i = 0;
    for (auto& ag : ags) {
        json::value j;
        j[U("id")] = json::value::number(ag.getId());
        j[U("horarioInicio")] = json::value::string(utility::conversions::to_string_t(tmParaString(ag.getHorarioInicio())));
        j[U("horarioFim")] = json::value::string(utility::conversions::to_string_t(tmParaString(ag.getHorarioFim())));
        result[i++] = j;
    }
    request.reply(status_codes::OK, result);
}

void AgendamentoControlador::buscarPorClienteId(http_request request) {
    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));
    if (paths.empty()) {
        request.reply(status_codes::BadRequest, U("ID do cliente não informado."));
        return;
    }
    int clienteId = std::stoi(utility::conversions::to_utf8string(paths[0]));
    auto ags = service.listarTodosPorCliente(clienteId);

    json::value result = json::value::array();
    int i = 0;
    for (auto& ag : ags) {
        json::value j;
        j[U("id")] = json::value::number(ag.getId());
        j[U("horarioInicio")] = json::value::string(utility::conversions::to_string_t(tmParaString(ag.getHorarioInicio())));
        j[U("horarioFim")] = json::value::string(utility::conversions::to_string_t(tmParaString(ag.getHorarioFim())));
        result[i++] = j;
    }
    request.reply(status_codes::OK, result);
}

void AgendamentoControlador::atualizarHorario(http_request request) {
    request.extract_json().then([this, request](pplx::task<json::value> task) mutable {
        try {
            json::value j = task.get();
            if (!j.has_field(U("id")) || !j.has_field(U("novoHorarioInicio"))) {
                request.reply(status_codes::BadRequest, U("Campos obrigatórios: id, novoHorarioInicio"));
                return;
            }

            int agendamentoId = j[U("id")].as_integer();
            std::string novoHorarioStr = utility::conversions::to_utf8string(j[U("novoHorarioInicio")].as_string());
            int r = service.mudarHorario(stringParaTm(novoHorarioStr), agendamentoId);

            request.reply(status_codes::OK, json::value::number(r));
        }
        catch (const std::exception& e) {
            request.reply(status_codes::BadRequest, utility::conversions::to_string_t(e.what()));
        }
        });
}

void AgendamentoControlador::atualizarBarbeiro(http_request request) {
    request.extract_json().then([this, request](pplx::task<json::value> task) mutable {
        try {
            json::value j = task.get();
            if (!j.has_field(U("id")) || !j.has_field(U("novoBarbeiroId"))) {
                request.reply(status_codes::BadRequest, U("Campos obrigatórios: id, novoBarbeiroId"));
                return;
            }

            int agendamentoId = j[U("id")].as_integer();
            int novoBarbeiroId = j[U("novoBarbeiroId")].as_integer();
            int r = service.mudarBarbeiro(novoBarbeiroId, agendamentoId);

            request.reply(status_codes::OK, json::value::number(r));
        }
        catch (const std::exception& e) {
            request.reply(status_codes::BadRequest, utility::conversions::to_string_t(e.what()));
        }
        });
}

void AgendamentoControlador::deletarAgendamento(http_request request) {
    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));
    if (paths.empty()) {
        request.reply(status_codes::BadRequest, U("ID do agendamento não informado."));
        return;
    }
    int agendamentoId = std::stoi(utility::conversions::to_utf8string(paths[0]));
    int r = service.excluirAgendamento(agendamentoId);
    request.reply(status_codes::OK, json::value::number(r));
}
