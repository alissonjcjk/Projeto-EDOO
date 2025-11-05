#pragma once

#include "../Database.h"
#include "../modelos/Pessoa.h"
#include "../modelos/Barbeiro.h"
#include <string>
#include <vector>

class BarbeiroRepository {
private:
    Database& db;
    static std::string escape(const std::string& s);

public:
    BarbeiroRepository(Database& database);
    int createBarbeiro(Barbeiro barbeiro);
    std::vector<Barbeiro> findAllBarbeiros();
    Barbeiro buscarPorId(int id);
};
