#include "Pessoa.h"
#include <iostream>

using namespace std;

Pessoa::Pessoa(int id, string nome, string email, string telefone){
    this->id = id;
    this->nome = nome;
    this->email = email;
    this->telefone = telefone;
}


string Pessoa::getEmail(){
    return email;
}
string Pessoa::getNome(){
    return nome;
}