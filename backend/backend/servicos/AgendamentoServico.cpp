#include "AgendamentoServico.h"
#include <algorithm>
#include <cctype>

/*
	AgendamentoServico(AgendamentoRepositorio& r);
	int criarAgendamento(Agendamento agendamento);
	Agendamento buscaPor(int id);
	std::vector<Agendamento> listarTodos();
	std::vector<Agendamento> listarTodosPorBarbeiro(int id);
	std::vector<Agendamento> listarTodosPorCliente(int id);
	int mudarHorario(std::tm novoHorarioInicio, int agendamentoId);
	int mudarBarbeiro(int barbeiroId, int agendamentoId);
*/

AgendamentoServico::AgendamentoServico(AgendamentoRepositorio& r): repo(r){}

int AgendamentoServico::criar(int clienteId, int barbeiroId, int servicoId,
	const std::tm& horarioInicio, const std::tm& horarioFim) {
	return repo.criar(clienteId, barbeiroId, servicoId, horarioInicio, horarioFim);
}

Agendamento AgendamentoServico::buscaPor(int id) {
	return repo.buscarPor(id);
}

std::vector<Agendamento> AgendamentoServico::listarTodos() {
	return repo.listarTodos();
}

std::vector<Agendamento> AgendamentoServico::listarTodosPorBarbeiro(int id) {
	return repo.listarTodosAgendamentosPorBarbeiro(id);
}

std::vector<Agendamento> AgendamentoServico::listarTodosPorCliente(int id) {
	return repo.listarTodosAgendamentosPorCliente(id);
}

int AgendamentoServico::mudarHorario(std::tm novoHorarioInicio, int agendamentoId) {
	Agendamento ag = repo.buscarPor(agendamentoId);
	ag.reagendar(novoHorarioInicio);
	return repo.mudarData(ag.getHorarioInicio(), ag.getHorarioFim(), agendamentoId);
}

int AgendamentoServico::mudarBarbeiro(int novoBarbeiroId, int agendamentoId) {
	return repo.mudarBarbeiroResponsavel(novoBarbeiroId, agendamentoId);
}

int AgendamentoServico::excluirAgendamento(int agendamentoId) {
	return repo.deletarAgendamento(agendamentoId);
}