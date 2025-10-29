#pragma once

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
    Agendamento();
    Agendamento(int id, Cliente* cliente, Barbeiro* barbeiro, Servico* servico, const string& data, const string& horarioInicio, const string& horarioFim);

    // métodos de acesso
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

    // sets
    void setId(int novoId);
    void setCliente(Cliente* c);
    void setBarbeiro(Barbeiro* b);
    void setServico(Servico* s);
    void setData(const string& novaData);
    void setHorarioInicio(const string& novoHorarioInicio);
    void setHorarioFim(const string& novoHorarioFim);

    // exibição
    void exibir() const;
};
