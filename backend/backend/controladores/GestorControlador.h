#pragma once

#include "../servicos/GestorServico.h"
#include <cpprest/http_listener.h>

class GestorController {
private:
	GestorService& service; // Corrigido: nome correto da classe
public:
	GestorController(GestorService& svc);
	void criar(web::http::http_request request);
	void listAll(web::http::http_request request);
};