#pragma once
#include "../servicos/PessoaServico.h"
#include <cpprest/http_listener.h>

using namespace web::http::experimental::listener;
using namespace web::http;

class PessoaControlador {
private:
    PessoaServico& servico;

public:
    PessoaControlador(PessoaServico& svc);

    void mudarNome(http_request request);
    void mudarTelefone(http_request request);
};
