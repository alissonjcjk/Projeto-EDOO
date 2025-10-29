#include "../include/Agendamento.h"
#include "../include/Cliente.h"
#include "../include/Barbeiro.h"
#include "../include/Servico.h"

#include <iostream>
using namespace std;

// Construtor 
// vai ter que fazer um vetor de armazenamento na main. Cada posição será para um cliente e barbeiro ou o mesmo
//para ver se o barbeiro esta disponivel, terá que percorrer o vetor de agendamento e ver os clientes que foram agendados 
//com o barbeiro em questao e ver se os horarios nao batem com algum outro que queira agendar
// MÉTODOS DE ACESSO
void Agendamento::setAgendamento(int i, Cliente* cli, Barbeiro* bar, Servico* serv, const string& d, const string& horarioI, const string& horarioF){
    id = i;
    cliente = cli;
    barbeiro = bar;
    servico = serv;
    data = d;
    horarioInicio = horarioI;
    horarioFim = horarioF;
}

int Agendamento::getId() const {
    return id;
}

Cliente* Agendamento::getCliente() const {
    return cliente;
}

Barbeiro* Agendamento::getBarbeiro() const {
    return barbeiro;
}

Servico* Agendamento::getServico() const {
    return servico;
}

string Agendamento::gethorarioInicio() const {
    return horarioInicio;
}

string Agendamento::gethorarioFim() const {
    return horarioFim;
}

string Agendamento::getData() const {
    return data;
}

bool Agendamento::isConcluido() const {
    return concluido;
}


// MÉTODOS DE CONTROLE
void Agendamento::concluir() {
    concluido = true;
    cout << "Agendamento de ID " << id << " concluído." << endl;
}

void Agendamento::cancelar() {
    concluido = false;
    cout << "Agendamento de ID " << id << " cancelado." << endl;
}

void Agendamento::reagendar(const string& novaData, const string& novoHorarioInicio, const string& novoHorarioFim) {
    data = novaData;
    horarioInicio = novoHorarioInicio;
    horarioFim = novoHorarioFim;
    cout << "Agendamento de ID " << id << " reagendado para " << data << " às " << horarioInicio << "." << endl;
}

// EXIBIÇÂO
void Agendamento::exibir() const {
    cout << "Agendamento ID: " << id << endl;
    cout << "Cliente: " << (cliente ? cliente->getNome() : "N/A") << endl;
    cout << "Barbeiro: " << (barbeiro ? barbeiro->getNome() : "N/A") << endl;
    //cout << "Serviço: " << (servico ? servico->getDescricao() : "N/A") << endl;
    cout << "Data: " << data << endl;
    cout << "Hora: " << horarioInicio << endl;
    cout << "Status: " << (concluido ? "Concluído" : "Pendente") << endl;
}