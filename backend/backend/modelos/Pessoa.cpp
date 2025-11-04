#include "Pessoa.h"

Pessoa::Pessoa(int id, const std::string& nome, const std::string& email, const std::string& telefone)
    : id(id), nome(nome), email(email), telefone(telefone) {}

Pessoa::Pessoa(const std::string& nome, const std::string& email, const std::string& telefone)
    : nome(nome), email(email), telefone(telefone) {}

void Pessoa::setNome(const std::string& nome) {
    this->nome = nome;
}

void Pessoa::setEmail(const std::string& email) {
    this->email = email;
}

void Pessoa::setTelefone(const std::string& telefone) {
    this->telefone = telefone;
}

int Pessoa::getId() const {
    return id;
}

std::string Pessoa::getNome() const {
    return nome;
}

std::string Pessoa::getEmail() const {
    return email;
}

std::string Pessoa::getTelefone() const {
    return telefone;
}
