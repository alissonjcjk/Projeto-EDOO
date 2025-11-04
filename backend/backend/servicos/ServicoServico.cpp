/*
	ServicoServico(ServicoRepositorio& r);
	int cria(Servicos servico);
	int mudaValor(int servicoId, double novoValor);
	int mudaDuracao(int servicoId, int novaDuracao);
	Servicos buscarServicoPor(int id);
	std::vector<Servicos> listarTodos();
*/

#include "ServicoServico.h"
#include <algorithm>
#include <cctype>

ServicoServico::ServicoServico(ServicoRepositorio& r): repo(r) {}

int ServicoServico::cria(Servicos servico) {
    try
    {
        if (servico.getDuracao() < 5 || servico.getPreco() <= 0.0 || servico.getNome().empty()) {
            return -1;
        }

        return repo.criar(servico);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Erro ao criar serviço: " << e.what() << std::endl;
        return -1;
    }

}

Servicos ServicoServico::buscarServicoPor(int id) {
    try {
        return repo.buscarServicoPor(id);
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao buscar serviço: " << e.what() << std::endl;
        return Servicos();
    }
}

int ServicoServico::mudaValor(int id, double novoValor) {
    try {
        return repo.mudarValor(id, novoValor);
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao mudar valor do serviço: " << e.what() << std::endl;
        return -1;
    }
}

int ServicoServico::mudaDuracao(int id, int novaDuracao) {
    try {
        return repo.mudarDuracao(id, novaDuracao);
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao mudar duração do serviço: " << e.what() << std::endl;
        return -1;
    }
}

std::vector<Servicos> ServicoServico::listarTodos() {
    try {
        return repo.listarTodos();
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao listar serviços: " << e.what() << std::endl;
        return {};
    }
}