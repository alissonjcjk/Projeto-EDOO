#include "../include/Barba.h"
#include <iostream>

using namespace std;

// Construtor
Barba::Barba(float preco, const string& descricao)
    : preco(preco), descricao(descricao) {}

// MÉTODOS SOBREESCRITOS (polimorfismo)
void Barba::exibir() const {
    cout << "Serviço: " << descricao << ", Preço: R$ " << preco << endl;
}

// Variações no corte de barba
float Barba::calcularPreco() const {
    return preco;
    // por enquanto so retorna o preço fixo, da pra adicionar variações de barba
}

// MÉTODOS DE ACESSO E MODIFICAÇÃO
float Barba::getPreco() const { return preco; }

string Barba::getDescricao() const { return descricao;}

void Barba::setPreco(float novoPreco) { preco = novoPreco; }

void Barba::setDescricao(const string& novaDescricao) { descricao = novaDescricao; }
