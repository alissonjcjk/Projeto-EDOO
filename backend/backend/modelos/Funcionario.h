#pragma once

#include "Pessoa.h" 
#include <vector>   
using namespace std;

class Funcionario : public Pessoa {
private:
    float salario;
    //int horarioTrabalhoInicio;
    //int horarioTrabalhoTermino;
    vector<Funcionario*> funcionarios; 
public:
    Funcionario(int id, string nome, string email, string telefone, float salario);
    Funcionario(string nome, string email, string telefone, float salario);
    Funcionario();
    ~Funcionario();
    float getSalario() const;
    bool serDemitido(string nome);
    bool aumentarSalario(float valor, string nome);

};