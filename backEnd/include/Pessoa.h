#pragma once
#include <iostream>

using namespace std;

class Pessoa{
    private:
        string nome;
        string email;
    public:
        Pessoa(string n, string e);
        string getNome();
        string getEmail(); 
};