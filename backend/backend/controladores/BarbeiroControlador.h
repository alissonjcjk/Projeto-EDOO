#pragma once

#include "../servicos/BarbeiroServico.h"
#include <cpprest/http_listener.h>

class BarbeiroController {
private:
    BarbeiroService& service;
public:
    BarbeiroController(BarbeiroService& svc);
    void create(web::http::http_request request);
    void findAll(web::http::http_request request);
    void buscarPorId(web::http::http_request request);
};