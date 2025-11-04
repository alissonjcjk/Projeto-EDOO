#include "ArquivoManager.h"
#include <sstream>

using namespace std;

// Salvar Clientes
void ArquivoManager::salvarClientes(const vector<Cliente>& clientes) {
    ofstream arquivo("clientes.txt");
    if (arquivo.is_open()) {
        for (const auto& cliente : clientes) {
            arquivo << cliente.getId() << "|"
                   << cliente.getNome() << "|"
                   << cliente.getEmail() << "|"
                   << cliente.getTelefone() << "|"
                   << cliente.getServicoPreferido() << "\n";
        }
        arquivo.close();
    }
}

// Salvar Barbeiros
void ArquivoManager::salvarBarbeiros(const vector<Barbeiro>& barbeiros) {
    ofstream arquivo("barbeiros.txt");
    if (arquivo.is_open()) {
        for (const auto& barbeiro : barbeiros) {
            arquivo << barbeiro.getId() << "|"
                   << barbeiro.getNome() << "|"
                   << barbeiro.getEmail() << "|"
                   << barbeiro.getTelefone() << "|"
                   << barbeiro.getEspecialidade() << "\n";
        }
        arquivo.close();
    }
}

// Salvar Serviços
void ArquivoManager::salvarServicos(const vector<Servico>& servicos) {
    ofstream arquivo("servicos.txt");
    if (arquivo.is_open()) {
        for (const auto& servico : servicos) {
            arquivo << servico.getId() << "|"
                   << servico.getNome() << "|"
                   << servico.getPreco() << "|"
                   << servico.getDuracao() << "\n";
        }
        arquivo.close();
    }
}

// Salvar Agendamentos
void ArquivoManager::salvarAgendamentos(const vector<Agendamento>& agendamentos) {
    ofstream arquivo("agendamentos.txt");
    if (arquivo.is_open()) {
        for (const auto& agendamento : agendamentos) {
            arquivo << agendamento.getId() << "|"
                   << agendamento.getCliente()->getId() << "|"
                   << agendamento.getBarbeiro()->getId() << "|"
                   << agendamento.getServico()->getId() << "|"
                   << agendamento.getData() << "|"
                   << agendamento.gethorarioInicio() << "|"
                   << agendamento.gethorarioFim() << "\n";
        }
        arquivo.close();
    }
}

// Carregar Clientes
void ArquivoManager::carregarClientes(vector<Cliente>& clientes) {
    ifstream arquivo("clientes.txt");
    if (arquivo.is_open()) {
        string linha;
        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string token;
            vector<string> dados;
            
            while (getline(ss, token, '|')) {
                dados.push_back(token);
            }
            
            if (dados.size() == 5) {
                int id = stoi(dados[0]);
                Cliente cliente(id, dados[1], dados[2], dados[3], dados[4]);
                clientes.push_back(cliente);
            }
        }
        arquivo.close();
    }
}

// Carregar Barbeiros
void ArquivoManager::carregarBarbeiros(vector<Barbeiro>& barbeiros) {
    ifstream arquivo("barbeiros.txt");
    if (arquivo.is_open()) {
        string linha;
        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string token;
            vector<string> dados;
            
            while (getline(ss, token, '|')) {
                dados.push_back(token);
            }
            
            if (dados.size() == 5) {
                int id = stoi(dados[0]);
                Barbeiro barbeiro(0, 0, id, dados[1], dados[2], dados[3],dados[4]);
                barbeiros.push_back(barbeiro);
            }
        }
        arquivo.close();
    }
}

// Carregar Serviços
void ArquivoManager::carregarServicos(vector<Servico>& servicos) {
    ifstream arquivo("servicos.txt");
    if (arquivo.is_open()) {
        string linha;
        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string token;
            vector<string> dados;
            
            while (getline(ss, token, '|')) {
                dados.push_back(token);
            }
            
            if (dados.size() == 4) {
                int id = stoi(dados[0]);
                Servico servico(id);
                servico.setServico(dados[1], stof(dados[2]), stoi(dados[3]));
                servicos.push_back(servico);
            }
        }
        arquivo.close();
    }
}

// Carregar Agendamentos
void ArquivoManager::carregarAgendamentos(vector<Agendamento>& agendamentos) {
    ifstream arquivo("agendamentos.txt");
    if (arquivo.is_open()) {
        string linha;
        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string token;
            vector<string> dados;
            
            while (getline(ss, token, '|')) {
                dados.push_back(token);
            }
            
            if (dados.size() == 7) {
                int id = stoi(dados[0]);
                int idCliente = stoi(dados[1]);
                int idBarbeiro = stoi(dados[2]);
                int idServico = stoi(dados[3]);
                
                // Criar objetos temporários (em um sistema real, você buscaria nos vetores)
                Cliente* cliente = new Cliente(idCliente, "", "", "", "");
                Barbeiro* barbeiro = new Barbeiro(0, 0, idBarbeiro, "", "", "","");
                Servico* servico = new Servico(idServico);
                
                Agendamento agendamento;
                agendamento.setAgendamento(id, cliente, barbeiro, servico, dados[4], dados[5], dados[6]);
                agendamentos.push_back(agendamento);
            }
        }
        arquivo.close();
    }
}

// Métodos para obter últimos IDs
int ArquivoManager::obterUltimoIdCliente() {
    vector<Cliente> clientes;
    carregarClientes(clientes);
    return clientes.empty() ? 1 : clientes.back().getId() + 1;
}

int ArquivoManager::obterUltimoIdBarbeiro() {
    vector<Barbeiro> barbeiros;
    carregarBarbeiros(barbeiros);
    return barbeiros.empty() ? 1 : barbeiros.back().getId() + 1;
}

int ArquivoManager::obterUltimoIdServico() {
    vector<Servico> servicos;
    carregarServicos(servicos);
    return servicos.empty() ? 1 : servicos.back().getId() + 1;
}

int ArquivoManager::obterUltimoIdAgendamento() {
    vector<Agendamento> agendamentos;
    carregarAgendamentos(agendamentos);
    return agendamentos.empty() ? 1 : agendamentos.back().getId() + 1;
}