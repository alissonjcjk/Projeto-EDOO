#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#include "Cliente.h"
#include "Barbeiro.h"
#include "Servico.h"
#include <string>
#include <iostream>

using namespace std;

// Declarações antecipadas para evitar dependências circulares
class Cliente;
class Barbeiro;
class Servico;

class Agendamento 
{
private:
    int id; // identificador para cada agendamento
    Cliente* cliente;
    Barbeiro* barbeiro;
    Servico* servico;
    string data; // Formato: dia-mes-ano
    string horarioInicio; // Formato: hh:mm
    string horarioFim; 
    bool concluido;

public:
    // construtor

    // métodos de acesso
    void setAgendamento(int i, Cliente* cli, Barbeiro* bar, Servico* serv, const string& d, const string& horarioI, const string& horarioF);
    int getId() const;
    Cliente* getCliente() const;
    Barbeiro* getBarbeiro() const;
    Servico* getServico() const;
    string getData() const;
    string gethorarioInicio() const;
    string gethorarioFim() const;
    bool isConcluido() const;

    // métodos de controle
    void concluir();
    void cancelar();
    void reagendar(const string& novaData, const string& novaHorarioInicio, const string& novaHorarioFim);

    // exibição
    void exibir() const;
};

#endif