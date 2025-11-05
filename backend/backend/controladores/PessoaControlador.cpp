#include "PessoaControlador.h"
#include <cpprest/json.h>
#include <iostream>

using namespace web;
using namespace http;

PessoaControlador::PessoaControlador(PessoaServico& svc) : servico(svc) {}

void PessoaControlador::mudarNome(http_request request) {
    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));
    if (paths.size() < 2) {
        request.reply(status_codes::BadRequest, U("ID não informado"));
        return;
    }

    int id = std::stoi(utility::conversions::to_utf8string(paths[1]));

    request.extract_json().then([this, request, id](pplx::task<json::value> task) mutable {
        try {
            json::value j = task.get();
            if (!j.has_field(U("nome"))) {
                request.reply(status_codes::BadRequest, U("Campo 'nome' obrigatório"));
                return;
            }

            std::string novoNome = utility::conversions::to_utf8string(j[U("nome")].as_string());
            int res = servico.mudarNome(id, novoNome);

            if (res <= 0) {
                request.reply(status_codes::InternalError, U("Falha ao atualizar nome"));
                return;
            }

            request.reply(status_codes::OK, U("Nome atualizado com sucesso"));
        }
        catch (const std::exception& e) {
            request.reply(status_codes::BadRequest, utility::conversions::to_string_t(e.what()));
        }
        });
}

void PessoaControlador::mudarTelefone(http_request request) {
    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));
    if (paths.size() < 2) {
        request.reply(status_codes::BadRequest, U("ID não informado"));
        return;
    }

    int id = std::stoi(utility::conversions::to_utf8string(paths[1]));

    request.extract_json().then([this, request, id](pplx::task<json::value> task) mutable {
        try {
            json::value j = task.get();
            if (!j.has_field(U("telefone"))) {
                request.reply(status_codes::BadRequest, U("Campo 'telefone' obrigatório"));
                return;
            }

            std::string novoTelefone = utility::conversions::to_utf8string(j[U("telefone")].as_string());
            int res = servico.mudarTelefone(id, novoTelefone);

            if (res <= 0) {
                request.reply(status_codes::InternalError, U("Falha ao atualizar telefone"));
                return;
            }

            request.reply(status_codes::OK, U("Telefone atualizado com sucesso"));
        }
        catch (const std::exception& e) {
            request.reply(status_codes::BadRequest, utility::conversions::to_string_t(e.what()));
        }
        });
}
