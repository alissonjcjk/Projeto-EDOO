#include "Servico.h"

using namespace std;

Servicos::Servicos() : id(0), nome(""), preco(0.0), duracaoEmMinutos(0) {}

Servicos::Servicos(int id, const string& nome, double preco, int duracaoEmMinutos)
    : id(id), nome(nome), preco(preco), duracaoEmMinutos(duracaoEmMinutos) {
}

Servicos::Servicos(const string& nome, double preco, int duracaoEmMinutos)
    : nome(nome), preco(preco), duracaoEmMinutos(duracaoEmMinutos) {
}

int Servicos::getId() const { return id; }
void Servicos::setId(int novoId) { id = novoId; }

string Servicos::getNome() const { return nome; }
void Servicos::setNome(const string& novoNome) { nome = novoNome; }

double Servicos::getPreco() const { return preco; }
void Servicos::setPreco(double novoPreco) { preco = novoPreco; }

int Servicos::getDuracao() const { return duracaoEmMinutos; }
void Servicos::setDuracao(int novaDuracao) { duracaoEmMinutos = novaDuracao; }

void Servicos::exibirDados() const {
    cout << "ID: " << id << endl;
    cout << "Nome: " << nome << endl;
    cout << "Preco: R$ " << preco << endl;
    cout << "Duracao: " << duracaoEmMinutos << " minutos" << endl;
}