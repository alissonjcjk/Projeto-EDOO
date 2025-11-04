#include "ClienteControlador.h"
#include <cpprest/json.h>
#include <iostream>

using namespace web;
using namespace http;

ClienteControlador::ClienteControlador(ClienteServico& servico) : servico(servico) {}

void ClienteControlador::criar(http_request request) {
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
            int servicoPreferido = 0;
            if (j.has_field(U("servico_preferido")) && j[U("servico_preferido")].is_number()) servicoPreferido = j[U("servico_preferido")].as_integer();

            Cliente cliente(nome, email, telefone, servicoPreferido);

            int id = servico.cria(cliente);
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

void ClienteControlador::buscarPorId(http_request request) {
    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));
    if (paths.size() < 2) {
        request.reply(status_codes::BadRequest, U("ID do barbeiro não informado."));
        return;
    }

    int id = std::stoi(utility::conversions::to_utf8string(paths[1]));

    try
    {
        Cliente cliente = servico.buscarPor(id);

        if (cliente.getId() == 0) {
            request.reply(status_codes::NotFound, U("Cliente não encontrado."));
            return;
        }

        json::value out = json::value::object();
        out[U("id")] = json::value::number(cliente.getId());
        out[U("nome")] = json::value::string(utility::conversions::to_string_t(cliente.getNome()));
        out[U("email")] = json::value::string(utility::conversions::to_string_t(cliente.getEmail()));
        out[U("telefone")] = json::value::string(utility::conversions::to_string_t(cliente.getTelefone()));
        out[U("servico_preferido")] = json::value::number(cliente.getServicoPreferido());

        request.reply(status_codes::OK, out);
    }
    catch (const std::exception& e)
    {
        request.reply(status_codes::InternalError, utility::conversions::to_string_t(e.what()));
    }


}

void ClienteControlador::findAll(http_request request) {
    json::value result = json::value::array();
    auto pessoas = servico.listarClientes();
    int i = 0;
    for (auto& p : pessoas) {
        json::value j;
        j[U("id")] = json::value::number(p.getId());
        j[U("nome")] = json::value::string(utility::conversions::to_string_t(p.getNome()));
        j[U("email")] = json::value::string(utility::conversions::to_string_t(p.getEmail()));
        j[U("telefone")] = json::value::string(utility::conversions::to_string_t(p.getTelefone()));
        result[i++] = j;
        j[U("servico_preferido")] = json::value::string(utility::conversions::to_string_t(p.getTelefone()));
        result[i++] = j;
    }
    request.reply(status_codes::OK, result);
    return;
}