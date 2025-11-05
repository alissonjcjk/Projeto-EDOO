#pragma once

#include "../Database.h"
#include "ClienteRepositorio.h"
#include <string>
#include "../modelos/Cliente.h"

class ClienteRepositorio {
	private:
		Database& db;
		static std::string escape(const std::string& s);

	public:
		ClienteRepositorio(Database& database);
		int criar(Cliente cliente, int servicoPreferidoId);
		std::vector<Cliente> findAllClientes();
		Cliente buscarPorId(int id);
		int deletar(int idCliente);
};