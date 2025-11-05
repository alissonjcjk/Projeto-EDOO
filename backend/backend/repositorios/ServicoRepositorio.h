#pragma once

#include "../Database.h"
#include "../modelos/Servico.h"
#include <string>
#include <vector>

class ServicoRepositorio {
private:
	Database& db;
	static std::string escape(const std::string& s);
public:
	ServicoRepositorio(Database& database);
	int criar(Servicos sevico);
	int mudarValor(int servicoId, double novoValor);
	int mudarDuracao(int servicoId, int novaDuracao);
	Servicos buscarServicoPor(int id);
	std::vector<Servicos> listarTodos();
};