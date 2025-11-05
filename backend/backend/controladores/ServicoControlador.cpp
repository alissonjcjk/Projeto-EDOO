#include "ServicoControlador.h"
#include <cpprest/json.h>
#include <iostream>

using namespace web;
using namespace http;

ServicoControlador::ServicoControlador(ServicoServico& servico)
    : servico(servico) {}

void ServicoControlador::criar(http_request request) {
    request.extract_json().then([this, &request](pplx::task<json::value> task) {
        try {
            auto j = task.get(); 

            if (!j.has_field(U("nome")) || !j.has_field(U("preco")) || !j.has_field(U("duracao"))) {
                request.reply(status_codes::BadRequest, U("Campos obrigatórios: nome, preco, duracao."));
                return;
            }

            std::string nome = utility::conversions::to_utf8string(j[U("nome")].as_string());
            double preco = j[U("preco")].as_double();
            int duracao = j[U("duracao")].as_integer();

            Servicos s(nome, preco, duracao);
            int id = servico.cria(s);

            if (id <= 0) {
                request.reply(status_codes::InternalError, U("Falha ao criar serviço."));
                return;
            }

            json::value resposta = json::value::object();
            resposta[U("id")] = json::value::number(id);
            resposta[U("mensagem")] = json::value::string(U("Serviço criado com sucesso."));
            request.reply(status_codes::Created, resposta);
        }
        catch (const std::exception& e) {
            request.reply(status_codes::BadRequest, utility::conversions::to_string_t(e.what()));
        }
        catch (...) {
            request.reply(status_codes::InternalError, U("Erro desconhecido ao criar serviço."));
        }
        }).wait(); 
}

void ServicoControlador::buscarPorId(http_request request) {
    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));
    if (paths.size() < 2) {
        request.reply(status_codes::BadRequest, U("ID do serviço não informado."));
        return;
    }

    int id = std::stoi(utility::conversions::to_utf8string(paths[1]));
    try {
        Servicos s = servico.buscarServicoPor(id);
        if (s.getId() <= 0) {
            request.reply(status_codes::NotFound, U("Serviço não encontrado."));
            return;
        }

        json::value out = json::value::object();
        out[U("id")] = json::value::number(s.getId());
        out[U("nome")] = json::value::string(utility::conversions::to_string_t(s.getNome()));
        out[U("preco")] = json::value::number(s.getPreco());
        out[U("duracao")] = json::value::number(s.getDuracao());
        request.reply(status_codes::OK, out);
    }
    catch (const std::exception& e) {
        request.reply(status_codes::InternalError, utility::conversions::to_string_t(e.what()));
    }
}

void ServicoControlador::listarTodos(http_request request) {
    try {
        auto lista = servico.listarTodos();
        json::value result = json::value::array();

        int i = 0;
        for (auto& s : lista) {
            json::value j = json::value::object();
            j[U("id")] = json::value::number(s.getId());
            j[U("nome")] = json::value::string(utility::conversions::to_string_t(s.getNome()));
            j[U("preco")] = json::value::number(s.getPreco());
            j[U("duracao")] = json::value::number(s.getDuracao());
            result[i++] = j;
        }

        request.reply(status_codes::OK, result);
    }
    catch (const std::exception& e) {
        request.reply(status_codes::InternalError, utility::conversions::to_string_t(e.what()));
    }
}

void ServicoControlador::mudarValor(http_request request) {
    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));
    if (paths.size() < 3) { 
        request.reply(status_codes::BadRequest, U("ID do serviço não informado."));
        return;
    }

    int id = std::stoi(utility::conversions::to_utf8string(paths[1]));

    request.extract_json().then([this, id, request](pplx::task<json::value> task) mutable {
        try {
            auto j = task.get();
            if (!j.has_field(U("novo_valor"))) {
                request.reply(status_codes::BadRequest, U("Campo 'novo_valor' é obrigatório."));
                return;
            }

            double novoValor = j[U("novo_valor")].as_double();
            int ok = servico.mudaValor(id, novoValor);
            if (ok <= 0) {
                request.reply(status_codes::InternalError, U("Falha ao atualizar valor do serviço."));
                return;
            }

            request.reply(status_codes::OK, U("Valor do serviço atualizado com sucesso."));
        }
        catch (const std::exception& e) {
            request.reply(status_codes::BadRequest, utility::conversions::to_string_t(e.what()));
        }
        }).wait();
}

void ServicoControlador::mudarDuracao(http_request request) {
    auto paths = uri::split_path(uri::decode(request.relative_uri().path()));
    if (paths.size() < 3) { 
        request.reply(status_codes::BadRequest, U("ID do serviço não informado."));
        return;
    }

    int id = std::stoi(utility::conversions::to_utf8string(paths[1]));

    request.extract_json().then([this, id, request](pplx::task<json::value> task) mutable {
        try {
            auto j = task.get();
            if (!j.has_field(U("nova_duracao"))) {
                request.reply(status_codes::BadRequest, U("Campo 'nova_duracao' é obrigatório."));
                return;
            }

            int novaDuracao = j[U("nova_duracao")].as_integer();
            int ok = servico.mudaDuracao(id, novaDuracao);
            if (ok <= 0) {
                request.reply(status_codes::InternalError, U("Falha ao atualizar duração do serviço."));
                return;
            }

            request.reply(status_codes::OK, U("Duração do serviço atualizada com sucesso."));
        }
        catch (const std::exception& e) {
            request.reply(status_codes::BadRequest, utility::conversions::to_string_t(e.what()));
        }
        }).wait();
}