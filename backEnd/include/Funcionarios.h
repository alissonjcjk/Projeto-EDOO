#pragma once
#include "Pessoa.h"
#include <iostream>
#include <vector>

using namespace std;

class Funcionarios:public Pessoa{
        private:
            float salario;
            int horarioTrabalhoInicio;
            int horarioTrabalhoTermino;
        public:
            Funcionarios(int horarioInicio, int horarioFIm, int id, string nome, string email, string telefone);
            int getHorarioTrabalhoInicial();
            int getHorarioTrabalhoFinal();
            float getSalario();
           
};