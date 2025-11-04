#ifndef ARQUIVOMANAGER_H
#define ARQUIVOMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Cliente.h"
#include "Barbeiro.h"
#include "Servico.h"
#include "Agendamento.h"

class ArquivoManager {
public:
    // Métodos para salvar dados
    static void salvarClientes(const std::vector<Cliente>& clientes);
    static void salvarBarbeiros(const std::vector<Barbeiro>& barbeiros);
    static void salvarServicos(const std::vector<Servico>& servicos);
    static void salvarAgendamentos(const std::vector<Agendamento>& agendamentos);
    
    // Métodos para carregar dados
    static void carregarClientes(std::vector<Cliente>& clientes);
    static void carregarBarbeiros(std::vector<Barbeiro>& barbeiros);
    static void carregarServicos(std::vector<Servico>& servicos);
    static void carregarAgendamentos(std::vector<Agendamento>& agendamentos);
    
    // Métodos auxiliares
    static int obterUltimoIdCliente();
    static int obterUltimoIdBarbeiro();
    static int obterUltimoIdServico();
    static int obterUltimoIdAgendamento();
};

#endif