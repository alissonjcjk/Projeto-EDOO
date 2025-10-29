#include "Cliente.h"
#include "Agendamento.h"

// Construtor
Cliente::Cliente(int i, const string& n, const string& e, const string& t, const string& s)
    : Pessoa(i, n, e, t), servicoPreferido(s) {}

void Barbeiro::setAgendamento(int id, Cliente* cliente, Barbeiro* barbeiro, Servico* servico, const string& data, const string& horarioInicio, const string& horarioFim){
        agendamento.setAgendamento(id,cliente,barbeiro,servico,data,horarioInicio,horarioFim);
}

// Setter
void Cliente::setServicoPreferido(const string& servico) {this->servicoPreferido = servico;}

// Getter
string Cliente::getServicoPreferido() const { return servicoPreferido;}