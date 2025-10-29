#include <iostream>
#include "Funcionarios.h"
#include "Barbeiro.h"
#include <vector>
using namespace std;

class Gestor: public Funcionarios{

    public:
        Gestor(int horarioInicio, int horarioFIm, int id, string nome, string email, string telefone);
        vector<Barbeiro> demitir(vector<Barbeiro>barbeiros, string nome);
};