#pragma once
#include <iostream>

using namespace std;

class Pessoa{
    private:
        int id;
        string nome;
        string email;
        string telefone;
    public:
        Pessoa(int id, string nome, string email, string telefone);
        string getNome();
        string getEmail(); 
};