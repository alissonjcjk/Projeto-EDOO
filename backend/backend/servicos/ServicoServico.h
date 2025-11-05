#pragma once

#include "../repositorios/ServicoRepositorio.h"
#include "../modelos/Servico.h"
#include <vector>
#include <string>

class ServicoServico {
private:
	ServicoRepositorio& repo;
public:
	ServicoServico(ServicoRepositorio& r);
	int cria(Servicos servico);
	int mudaValor(int servicoId, double novoValor);
	int mudaDuracao(int servicoId, int novaDuracao);
	Servicos buscarServicoPor(int id);
	std::vector<Servicos> listarTodos();
};