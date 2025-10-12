#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

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
    string hora; // Formato: hora:minuto
    bool concluido;
    bool cancelado;

public:
    // construtor
    Agendamento(int id, Cliente* cliente, Barbeiro* barbeiro, Servico* servico, const string& data, const string& hora);

    // métodos de acesso
    int getId() const;
    Cliente* getCliente() const;
    Barbeiro* getBarbeiro() const;
    Servico* getServico() const;
    string getHora() const;
    string getData() const;
    bool isConcluido() const;

    // métodos de controle
    void concluir();
    void cancelar();
    void reagendar(const string& novaData, const string& novaHora);
    void exibir() const;
};

#endif