#pragma once

#include "../repositorios/ClienteRepositorio.h"
#include "../modelos/Cliente.h"
#include <string>
#include <vector>

class ClienteServico {
private:
	ClienteRepositorio& repo;
public:
	ClienteServico(ClienteRepositorio& r);
	int cria(Cliente cliente);
	Cliente buscarPor(int id);
	std::vector<Cliente> listarClientes();
};