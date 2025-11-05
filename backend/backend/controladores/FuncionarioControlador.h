#pragma once
#include "../servicos/FuncionarioServico.h"
#include <cpprest/http_listener.h>

using namespace web::http::experimental::listener;

class FuncionarioControlador {
private:
    FuncionarioServico& service;

public:
    FuncionarioControlador(FuncionarioServico& svc);

    void deletar(web::http::http_request request);
    void aumentarSalario(web::http::http_request request);
};
