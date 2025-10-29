#include "../include/Agendamento.h"
#include "../include/Cliente.h"
#include "../include/Barbeiro.h"
#include "../include/Servico.h"

#include <iostream>
using namespace std;


// Construtr padrão
Agendamento::Agendamento()
    : id(0), cliente(nullptr), barbeiro(nullptr), servico(nullptr), data(""), horarioInicio(""), horarioFim(""), concluido(false) {}

// Construtor
Agendamento::Agendamento(int id, Cliente* cliente, Barbeiro* barbeiro, Servico* servico, const string& data, const string& horarioInicio, const string& horarioFim)
    : id(id), cliente(cliente), barbeiro(barbeiro), 
    servico(servico), data(data), horarioInicio(horarioInicio), horarioFim(horarioFim), concluido(false) {}

// MÉTODOS DE ACESSO
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
    cout << "Serviço: " << (servico ? servico->getDescricao() : "N/A") << endl;
    cout << "Data: " << data << endl;
    cout << "Hora: " << horarioInicio << endl;
    cout << "Status: " << (concluido ? "Concluído" : "Pendente") << endl;
}

// SETS
void Agendamento::setId(int novoId) {
    id = novoId;
}

void Agendamento::setCliente(Cliente* c) {
    cliente = c;
}

void Agendamento::setBarbeiro(Barbeiro* b) {
    barbeiro = b;
}

void Agendamento::setServico(Servico* s) {
    servico = s;
}

void Agendamento::setData(const string& novaData) {
    data = novaData;
}

void Agendamento::setHorarioInicio(const string& novoHorarioInicio) {
    horarioInicio = novoHorarioInicio;
}

void Agendamento::setHorarioFim(const string& novoHorarioFim) {
    horarioFim = novoHorarioFim;
}

