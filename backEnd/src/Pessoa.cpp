#include "Pessoa.h"
#include <iostream>

using namespace std;

Pessoa::Pessoa(string n, string e){
    nome = n;
    email = e;
}

string Pessoa::getEmail(){
    return email;
}
string Pessoa::getNome(){
    return nome;
}