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
            vector<Funcionarios*> funcionarios;// alocação dinâmica para formar um vetor de funcionarios
        public:
            Funcionarios(int horarioInicio, int horarioFIm, int id, string nome, string email, string telefone);
            ~Funcionarios();
            int getHorarioTrabalhoInicial();
            int getHorarioTrabalhoFinal();
            float getSalario();
            bool serDemitido(string nome);
            bool aumentarSalario(float valor, string nome);
           
};