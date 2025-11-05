#include "FuncionarioControlador.h"
#include <cpprest/json.h>
#include <iostream>

using namespace web;
using namespace http;

FuncionarioControlador::FuncionarioControlador(FuncionarioServico& svc) : service(svc) {}

void FuncionarioControlador::deletar(http_request request) {
    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));
    if (paths.size() < 2) {
        request.reply(status_codes::BadRequest, U("ID do funcionario não informado."));
        return;
    }

    int id = std::stoi(utility::conversions::to_utf8string(paths[1]));

    try {
        int res = service.deletarFuncionario(id);
        if (res <= 0) {
            request.reply(status_codes::NotFound, U("Funcionario não encontrado ou nao pode ser deletado."));
            return;
        }

        json::value out = json::value::object();
        out[U("mensagem")] = json::value::string(U("Funcionario deletado com sucesso"));
        request.reply(status_codes::OK, out);
    }
    catch (const std::exception& e) {
        request.reply(status_codes::InternalError, utility::conversions::to_string_t(e.what()));
    }
}

void FuncionarioControlador::aumentarSalario(http_request request) {
    request.extract_json().then([this, request](pplx::task<json::value> task) mutable {
        try {
            json::value j = task.get();
            if (!j.has_field(U("id")) || !j.has_field(U("valor"))) {
                request.reply(status_codes::BadRequest, U("Campos obrigatórios: id e valor"));
                return;
            }

            int id = j[U("id")].as_integer();
            double valor = j[U("valor")].as_double();

            if (service.aumentarSalario(id, valor)) {
                json::value out = json::value::object();
                out[U("mensagem")] = json::value::string(U("Salário aumentado com sucesso"));
                request.reply(status_codes::OK, out);
            }
            else {
                request.reply(status_codes::InternalError, U("Falha ao aumentar salário"));
            }
        }
        catch (const std::exception& e) {
            request.reply(status_codes::BadRequest, utility::conversions::to_string_t(e.what()));
        }
        catch (...) {
            request.reply(status_codes::InternalError, U("Erro desconhecido"));
        }
        });
}
