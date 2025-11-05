#pragma once

#include "../repositorios/GestorRepositorio.h"
#include <string>
#include "../modelos/Gestor.h"
#include <vector>

class GestorService {
	private:
		GestorRepositorio& repo;
	public:
		GestorService(GestorRepositorio& r); 
		int criarGestor(Gestor gestor);
		std::vector<Gestor> listarGestores();
};