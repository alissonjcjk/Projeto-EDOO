#pragma once
#include "../servicos/ServicoServico.h"
#include <cpprest/http_listener.h>

class ServicoControlador {
private:
    ServicoServico& servico;

public:
    ServicoControlador(ServicoServico& servico);
    void criar(web::http::http_request request);
    void buscarPorId(web::http::http_request request);
    void listarTodos(web::http::http_request request);
    void mudarValor(web::http::http_request request);
    void mudarDuracao(web::http::http_request request);
};