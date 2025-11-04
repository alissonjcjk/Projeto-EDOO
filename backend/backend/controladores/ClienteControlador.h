#pragma once

#include "../servicos//ClienteServico.h"
#include <cpprest/http_listener.h>

class ClienteControlador {
	private: 
		ClienteServico& servico;
	public:
		ClienteControlador(ClienteServico& servico);
		void criar(web::http::http_request request);
		void findAll(web::http::http_request request);
		void buscarPorId(web::http::http_request request);
};