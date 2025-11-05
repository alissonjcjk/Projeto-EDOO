#pragma once

#include "../repositorios/AgendamentoRepositorio.h"
#include "../modelos/Agendamento.h"
#include <string>
#include <vector>
#include <ctime>

class AgendamentoServico {
private:
	AgendamentoRepositorio& repo;
public:
	AgendamentoServico(AgendamentoRepositorio& r);
	int criar(int clienteId, int barbeiroId, int servicoId,
		const std::tm& horarioInicio, const std::tm& horarioFim);
	Agendamento buscaPor(int id);
	std::vector<Agendamento> listarTodos();
	std::vector<Agendamento> listarTodosPorBarbeiro(int id);
	std::vector<Agendamento> listarTodosPorCliente(int id);
	int mudarHorario(std::tm novoHorarioInicio, int agendamentoId);
	int mudarBarbeiro(int barbeiroId, int agendamentoId);
	int excluirAgendamento(int agendamentoId);
};