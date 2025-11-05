#pragma once


#include "../Database.h"
#include "../modelos/Pessoa.h"
#include <string>
#include "../modelos/Gestor.h"
#include <vector>

class GestorRepositorio {
	private:
		Database& db;
		static std::string escape(const std::string& s);
	public:
		GestorRepositorio(Database& database);
		int criarGestor(Gestor& gestor);
		std::vector<Gestor> findAllGestores();
};