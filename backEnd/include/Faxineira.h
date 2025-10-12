#pragma once
#include "Funcionarios.h"
#include <iostream>

using namespace std;

class Faxineira: public Funcionarios{
    public:
        Faxineira(float salario, string prof, string email);
};