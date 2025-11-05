#include "Agendamento.h"
#include "Cliente.h"
#include "Barbeiro.h"
#include "Servico.h"
#include <iomanip>
#include <sstream>

using namespace std;

Agendamento::Agendamento(int id, Cliente* cliente, Barbeiro* barbeiro, Servicos* servico,
    const std::tm horarioInicio, const std::tm horarioFim)
    : id(id),
    cliente(cliente),
    barbeiro(barbeiro),
    servico(servico),
    horarioInicio(horarioInicio),
    horarioFim(horarioFim) {
    std::time_t fim = std::mktime(const_cast<std::tm*>(&horarioFim));
    std::time_t agora = std::time(nullptr);

    concluido = (std::difftime(fim, agora) < 0);
}

Agendamento::Agendamento(Cliente* cliente, Barbeiro* barbeiro, Servicos* servico,
    const std::tm horarioInicio)
    : id(0),
    cliente(cliente),
    barbeiro(barbeiro),
    servico(servico),
    horarioInicio(horarioInicio),
    horarioFim(horarioInicio),
    concluido(false) {}

Agendamento::Agendamento()
    : id(0),
    cliente(nullptr),
    barbeiro(nullptr),
    servico(nullptr),
    concluido(false) {
    std::tm t = {};
    horarioInicio = t;
    horarioFim = t;
}

int Agendamento::getId() const { return id; }
Cliente* Agendamento::getCliente() const { return cliente; }
int Agendamento::getClienteId() const { return cliente->getId(); }
Barbeiro* Agendamento::getBarbeiro() const { return barbeiro; }
int Agendamento::getBarbeiroId() const { return barbeiro->getId(); }
Servicos* Agendamento::getServico() const { return servico; }
int Agendamento::getServicoId() const { return servico->getId(); }
bool Agendamento::isConcluido() const { return concluido; }

static string tmParaString(const std::tm& t, const string& formato) {
    stringstream ss;
    ss << put_time(&t, formato.c_str());
    return ss.str();
}

std::tm Agendamento::getHorarioInicio() const {
    return horarioInicio;
}

std::tm Agendamento::getHorarioFim() const {
    return horarioFim;
}

void Agendamento::concluir() {
    concluido = true;
}

void Agendamento::cancelar() {
    concluido = false;
}

void Agendamento::reagendar(std::tm& novoHorarioInicio) {
    time_t t = mktime(&novoHorarioInicio);
    t += servico->getDuracao() * 60;

    std::tm temp = {};
    localtime_s(&temp, &t);
    horarioFim = temp;

    horarioInicio = novoHorarioInicio;
}

void Agendamento::exibir() const {
    cout << "Agendamento ID: " << id << endl;
    cout << "Cliente: " << (cliente ? "OK" : "NULO") << endl;
    cout << "Barbeiro: " << (barbeiro ? "OK" : "NULO") << endl;
    cout << "Serviço: " << (servico ? "OK" : "NULO") << endl;
    cout << "Concluído: " << (concluido ? "Sim" : "Não") << endl;
    cout << "----------------------------------------" << endl;
}