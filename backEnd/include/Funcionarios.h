#pragma once
#include "Pessoa.h"
#include <iostream>

using namespace std;

class Funcionarios:public Pessoa{
        private:
            float salario;
            int qtdFunfionarios;
        public:
            Funcionarios(float salario, string funcio, string email);
            void addFuncionario();
            float getSalario();

};