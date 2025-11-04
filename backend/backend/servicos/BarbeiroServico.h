#pragma once

#include "../repositorios/BarbeiroRepositorio.h"
#include <string>
#include "../modelos/Barbeiro.h"
#include <vector>
#include "../modelos/Pessoa.h"

class BarbeiroService {
    private:
        BarbeiroRepository& repo;
    public:
        BarbeiroService(BarbeiroRepository& r);
        int criarBarbeiro(Barbeiro barbeiro);
        Barbeiro buscarPorId(int id);
        std::vector<Barbeiro> listarBarbeiros();
};