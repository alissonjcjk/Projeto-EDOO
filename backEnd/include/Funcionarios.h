#pragma once
#include "Pessoa.h"
#include <iostream>

using namespace std;
struct osFuncionarios
{
    string nome = "";
    string funcao = "";
};


class Funcionarios:public Pessoa{
        private:
            osFuncionarios funcio[10];
            float salario;
            int qtdFunfionarios;
        public:
            Funcionarios(float salario,string funcao, string funcio, string email);
            void addFuncionario(string nome, string funcao);
            float getSalario();
            void setFuncionario();
            osFuncionarios* getFuncionarios();
};