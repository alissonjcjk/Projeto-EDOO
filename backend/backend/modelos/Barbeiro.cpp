#include "Barbeiro.h"
#include <iostream>
using namespace std;

Barbeiro::Barbeiro(int id, const std::string& nome,
    const std::string& email, const std::string& telefone,
    float salario)
    : Funcionario(id, nome, email, telefone, salario){}



Barbeiro::Barbeiro(const std::string& nome,
    const std::string& email, const std::string& telefone,
    float salario)
    : Funcionario(nome, email, telefone, salario) {}

