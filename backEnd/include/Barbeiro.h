#pragma once
#include "Funcionarios.h"
#include <iostream>

using namespace std;

class Barbeiro: public Funcionarios{
    public:
        Barbeiro(float salario, string prof, string email);
};