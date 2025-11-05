#pragma once
#include "../servicos/AgendamentoServico.h"
#include "../modelos/Agendamento.h"
#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

class AgendamentoControlador {
private:
    AgendamentoServico& service;

    std::tm stringParaTm(const std::string& dataHoraStr);

public:
    AgendamentoControlador(AgendamentoServico& svc);

    void criar(http_request request);
    void buscarPorId(http_request request);
    void listarTodos(http_request request);
    void buscarPorBarbeiroId(http_request request);
    void buscarPorClienteId(http_request request);
    void atualizarHorario(http_request request);
    void atualizarBarbeiro(http_request request);
    void deletarAgendamento(http_request request);
};