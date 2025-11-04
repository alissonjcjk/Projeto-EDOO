#pragma once

#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#include <string>
#include <iostream>

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
    Servico* servico;
    string data; // Formato: dia-mes-ano
    string horarioInicio; // Formato: hh:mm
    string horarioFim;
    bool concluido;

public:
    Agendamento(int id, Cliente* cliente, Barbeiro* barbeiro, Servico* servico, const string& data, const string& horarioInicio, const string& horarioFim);

    int getId() const;
    Cliente* getCliente() const;
    Barbeiro* getBarbeiro() const;
    Servico* getServico() const;
    string getData() const;
    string gethorarioInicio() const;
    string gethorarioFim() const;
    bool isConcluido() const;

    void concluir();
    void cancelar();
    void reagendar(const string& novaData, const string& novaHorarioInicio, const string& novaHorarioFim);


    void exibir() const;
};

#endif