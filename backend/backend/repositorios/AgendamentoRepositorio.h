#pragma once

#include "../Database.h"
#include "../modelos/Agendamento.h"
#include "../modelos/Barbeiro.h"
#include "../modelos/Cliente.h"
#include "../modelos/Servico.h"
#include <string>
#include <vector>

class AgendamentoRepositorio {
private:
	Database& db;
	static std::string escape(const std::string& s);
	static string tmParaString(const std::tm& t);

public:
	AgendamentoRepositorio(Database& database);
	int criar(int clienteId, int barbeiroId, int servicoId,
		const std::tm& horarioInicio, const std::tm& horarioFim);
	std::vector<Agendamento> listarTodos();
	std::vector<Agendamento> listarTodosAgendamentosPorBarbeiro(int id);
	std::vector<Agendamento> listarTodosAgendamentosPorCliente(int id);
	int mudarBarbeiroResponsavel(int novoBarbeiroId, int agendamentoId);
	int mudarData(std::tm horarioInicio, std::tm horarioFim, int agendamentoId);
	int deletarAgendamento(int agendamentoId);
	Agendamento buscarPor(int id);
};
