#pragma once
#include <iostream>

using namespace std;

class Servico{
    private:
        int id;
        string nome;
        float preco;
        int duracao;
    public:
    //ver o construtor
        Servico(int id);
        void setServico(string nome, float preco, int duracao); 
        int getId() const;
        string getNome() const;
        double getPreco() const;
        int getDuracao() const;
};