#pragma once
#include <iostream>
#include <string>

using namespace std;

class Pessoa{
private:
    int id;
    string nome;
    string email;
    string telefone;

public:
    /* 
    Passando os endereços de memória para não ficar copiando as informações da pessoa toda vez que chamar o cosntrutor
    */

    Pessoa(int id, const string& nome, const string& email, const string& telefone);

    // Setters
    // Passando os endereços de memória
    void setNome(const string& nome);
    void setEmail(const string& email);
    void setTelefone(const string& telefone);

    // Getters
    // Colocando "const" para explicitar que o método apenas lê o atributo
    int getId() const;
    string getNome() const;
    string getEmail() const;
    string getTelefone() const;
};