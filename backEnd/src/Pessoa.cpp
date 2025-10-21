#include "Pessoa.h"

// Construtor
Pessoa::Pessoa(int i, const string& n, const string& e, const string& t)
    : id(i), nome(n), email(e), telefone(t) {}

// Setters
void Pessoa::setNome(const string& nome) {this->nome = nome;}
void Pessoa::setEmail(const string& email) {this->email = email;} // Talvez precise fazer tratamento de erro...
void Pessoa::setTelefone(const string& telefone) {this->telefone = telefone;}

// Getters
int Pessoa::getId() const { return id;}
string Pessoa::getNome() const { return nome;}
string Pessoa::getEmail() const { return email;}
string Pessoa::getTelefone() const { return telefone;}