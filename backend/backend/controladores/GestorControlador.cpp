#include "GestorControlador.h"
#include <cpprest/json.h>
#include <iostream>
#include "../modelos/Gestor.h"

using namespace web;
using namespace http;

GestorController::GestorController(GestorService& svc) : service(svc) {}

void GestorController::criar(http_request request) {
	request.extract_json().then([this, request](pplx::task<json::value> task) mutable {
		try {
			json::value j = task.get();
			if (!j.has_field(U("nome")) || !j.has_field(U("email")) || !j.has_field(U("telefone"))) {
				request.reply(status_codes::BadRequest, U("Campos obrigatrios: nome, email, telefone"));
				return;
			}
			std::string nome = utility::conversions::to_utf8string(j[U("nome")].as_string());
			std::string email = utility::conversions::to_utf8string(j[U("email")].as_string());
			std::string telefone = utility::conversions::to_utf8string(j[U("telefone")].as_string());
			double salario = 0.0;
			if (j.has_field(U("salario")) && j[U("salario")].is_number()) salario = j[U("salario")].as_double();

			Gestor gestor(nome, email, telefone, salario);

			int id = service.criarGestor(gestor);
			if (id <= 0) {
				request.reply(status_codes::InternalError, U("Falha ao criar gestor"));
				return;
			}
			json::value out = json::value::object();
			out[U("id")] = json::value::number(id);
			out[U("mensagem")] = json::value::string(U("Gestor criado com sucesso"));
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

void GestorController::listAll(http_request request) {
	try {
		std::vector<Gestor> gestores = service.listarGestores();
		json::value result = json::value::array();

		int index = 0;
		for (const auto& g : gestores) {
			json::value j;
			j[U("id")] = json::value::number(g.getId());
			j[U("nome")] = json::value::string(utility::conversions::to_string_t(g.getNome()));
			j[U("email")] = json::value::string(utility::conversions::to_string_t(g.getEmail()));
			j[U("telefone")] = json::value::string(utility::conversions::to_string_t(g.getTelefone()));
			j[U("salario")] = json::value::number(g.getSalario());
			result[index++] = j;
		}

		request.reply(status_codes::OK, result);
	}
	catch (const std::exception& e) {
		request.reply(status_codes::InternalError, utility::conversions::to_string_t(e.what()));
	}
}
