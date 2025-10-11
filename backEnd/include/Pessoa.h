#pragma once
#include <iostream>

using namespace std;

class Pessoa{
    private:
        Pessoa(string n, string e);
        string nome;
        string email;
    public:
        string getNome();
        string getEmail(); 
};