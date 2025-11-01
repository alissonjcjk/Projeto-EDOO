#include "Barbeiro.h"
#include "Agendamento.h"
#include "Barbeiro.h"
#include "Cliente.h"
#include "Servico.h"
#include <iostream>
using namespace std;


Barbeiro::Barbeiro(int horarioInicio, int horarioFIm, int id, string nome, string email, string telefone):
Funcionarios(horarioInicio,horarioFIm,id,nome,email,telefone){}

// void Barbeiro::setAgendamento(int id, Cliente* cliente, Barbeiro* barbeiro, Servico* servico, const string& data, const string& horarioInicio, const string& horarioFim){
//     agendamento->setAgendamento(id,cliente,barbeiro,servico,data,horarioInicio,horarioFim);
// }

