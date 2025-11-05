#pragma once

#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#include <string>
#include <iostream>
#include <ctime>
#include "Cliente.h"
#include "Barbeiro.h"
#include "Servico.h"

using namespace std;

class Cliente;
class Barbeiro;
class Servico;

class Agendamento
{
private:
    const int id; // identificador para cada agendamento
    Cliente* cliente;
    Barbeiro* barbeiro;
    Servicos* servico;
    std::tm horarioInicio; // Formato: hh:mm
    std::tm horarioFim;
    bool concluido;

public:
    Agendamento(int id, Cliente* cliente, Barbeiro* barbeiro, Servicos* servico, const std::tm horarioInicio, const std::tm horarioFim);
    Agendamento(Cliente* cliente, Barbeiro* barbeiro, Servicos* servico, const std::tm horarioInicio);
    Agendamento();

    int getId() const;
    Cliente* getCliente() const;
    int getClienteId() const;
    Barbeiro* getBarbeiro() const;
    int getBarbeiroId() const;
    Servicos* getServico() const;
    int getServicoId() const;
    std::tm getHorarioInicio() const;
    std::tm getHorarioFim() const;
    bool isConcluido() const;

    void concluir();
    void cancelar();
    void reagendar(std::tm& novaHorarioInicio);


    void exibir() const;
};

#endif