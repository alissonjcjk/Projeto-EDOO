#include "BarbeiroControlador.h"
#include <cpprest/json.h>
#include <iostream>

using namespace web;
using namespace http;

BarbeiroController::BarbeiroController(BarbeiroService& svc) : service(svc) {}

void BarbeiroController::create(http_request request) {
    request.extract_json().then([this, request](pplx::task<json::value> task) mutable {
        try {
            json::value j = task.get();
            if (!j.has_field(U("nome")) || !j.has_field(U("email")) || !j.has_field(U("telefone"))) {
                request.reply(status_codes::BadRequest, U("Campos obrigatorios: nome, email, telefone"));
                return;
            }

            std::string nome = utility::conversions::to_utf8string(j[U("nome")].as_string());
            std::string email = utility::conversions::to_utf8string(j[U("email")].as_string());
            std::string telefone = utility::conversions::to_utf8string(j[U("telefone")].as_string());
            double salario = 0.0;
            if (j.has_field(U("salario")) && j[U("salario")].is_number()) salario = j[U("salario")].as_double();

            Barbeiro barbeiro(nome, email, telefone, salario);

            int id = service.criarBarbeiro(barbeiro);
            if (id <= 0) {
                request.reply(status_codes::InternalError, U("Falha ao criar barbeiro"));
                return;
            }

            json::value out = json::value::object();
            out[U("id")] = json::value::number(id);
            out[U("mensagem")] = json::value::string(U("Barbeiro criado com sucesso"));
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

void BarbeiroController::buscarPorId(http_request request) {
    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));
    if (paths.size() < 2) {
        request.reply(status_codes::BadRequest, U("ID do barbeiro não informado."));
        return;
    }

    int id = std::stoi(utility::conversions::to_utf8string(paths[1]));

    try
    {
        Barbeiro barbeiro = service.buscarPorId(id);

        if (barbeiro.getId() == 0) {
            request.reply(status_codes::NotFound, U("Barbeiro não encontrado."));
            return;
        }

        json::value out = json::value::object();
        out[U("id")] = json::value::number(barbeiro.getId());
        out[U("nome")] = json::value::string(utility::conversions::to_string_t(barbeiro.getNome()));
        out[U("email")] = json::value::string(utility::conversions::to_string_t(barbeiro.getEmail()));
        out[U("telefone")] = json::value::string(utility::conversions::to_string_t(barbeiro.getTelefone()));
        out[U("salario")] = json::value::number(barbeiro.getSalario());

        request.reply(status_codes::OK, out);
    }
    catch (const std::exception& e)
    {
        request.reply(status_codes::InternalError, utility::conversions::to_string_t(e.what()));
    }

    
}

void BarbeiroController::findAll(http_request request) {
    json::value result = json::value::array();
    auto pessoas = service.listarBarbeiros();
    int i = 0;
    for (auto& p : pessoas) {
        json::value j;
        j[U("id")] = json::value::number(p.getId());
        j[U("nome")] = json::value::string(utility::conversions::to_string_t(p.getNome()));
        j[U("email")] = json::value::string(utility::conversions::to_string_t(p.getEmail()));
        j[U("telefone")] = json::value::string(utility::conversions::to_string_t(p.getTelefone()));
        result[i++] = j;
    }
    request.reply(status_codes::OK, result);
    return;
}