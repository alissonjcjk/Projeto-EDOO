#include "Servico.h"
#include <iostream>

using namespace std;

Servico::Servico(int id){
    this->id = id;
}

void Servico::setServico(string nome, float preco, int duracao){
    this->nome = nome;
    this->preco = preco;
    this->duracao = duracao;
}