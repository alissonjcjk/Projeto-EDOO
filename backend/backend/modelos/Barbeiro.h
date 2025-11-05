#pragma once

#include <vector>
#include "Funcionario.h"
#include <iostream>

using namespace std;

class Barbeiro : public Funcionario {
public:
    Barbeiro(int id, const std::string& nome, const std::string& email,
        const std::string& telefone, float salario);


    Barbeiro(const std::string& nome, const std::string& email,
        const std::string& telefone, float salario);


    Barbeiro()
        : Funcionario() {};

};