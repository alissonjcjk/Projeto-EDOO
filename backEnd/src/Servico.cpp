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

int Servico::getId() const{
    return id;
}

string Servico::getNome() const{
    return nome;
}

double Servico::getPreco() const{
    return preco;
}

int Servico::getDuracao() const{
    return duracao;
}