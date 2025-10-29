#include <iostream>
#include <vector>
#include "Cliente.h"
#include "Barbeiro.h"
#include "Servico.h"
#include "Agendamento.h"
#include "Gestor.h"

using namespace std;

int main() {
    vector<Cliente> clientes;
    vector<Barbeiro> barbeiros;
    vector<Servico> servicos;
    vector<Agendamento> agendamentos;
    vector<Gestor> gestores;

    int idAgendamento = 1;
    int opcao;

    do {
        cout << "\n===== MENU BARBEARIA =====\n";
        cout << "1. Cadastrar Cliente\n";
        cout << "2. Cadastrar Barbeiro\n";
        cout << "5. Cadastrar Gestor \n"; // modificar
        cout << "3. Agendar Horário\n";
        cout << "4. Exibir Agendamentos\n";
        cout << "5. Exibir Barbeiros Cadastrados\n";
        cout << "6. Exibir Clientes Cadastrados\n";
        cout << "7. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                // Cadastrar Cliente
                string nome, telefone;
                cout << "Digite o nome do cliente: ";
                cin.ignore();  // Limpa o buffer
                getline(cin, nome);
                cout << "Digite o telefone do cliente: ";
                getline(cin, telefone);
                clientes.push_back(Cliente(nome, telefone));
                cout << "Cliente cadastrado com sucesso!\n";
                break;
            }

            case 2: {
                // Cadastrar Barbeiro
                string nome, especialidade;
                cout << "Digite o nome do barbeiro: ";
                cin.ignore();  // Limpa o buffer
                getline(cin, nome);
                cout << "Digite a especialidade do barbeiro: ";
                getline(cin, especialidade);
                barbeiros.push_back(Barbeiro(nome, especialidade));
                cout << "Barbeiro cadastrado com sucesso!\n";
                break;
            }

            case 3: {
                // Agendar horário
                if (clientes.empty() || barbeiros.empty() || servicos.empty()) {
                    cout << "Certifique-se de que há clientes, barbeiros e serviços cadastrados antes de agendar!\n";
                    break;
                }

                string data, horarioInicio, horarioFim;
                int idCliente, idBarbeiro, idServico;
                
                // Escolher cliente
                cout << "Escolha o cliente (1 a " << clientes.size() << "): ";
                cin >> idCliente;
                Cliente* clienteEscolhido = &clientes[idCliente - 1];

                // Escolher barbeiro
                cout << "Escolha o barbeiro (1 a " << barbeiros.size() << "): ";
                cin >> idBarbeiro;
                Barbeiro* barbeiroEscolhido = &barbeiros[idBarbeiro - 1];

                // Escolher serviço
                cout << "Escolha o serviço (1 a " << servicos.size() << "): ";
                cin >> idServico;
                Servico* servicoEscolhido = &servicos[idServico - 1];

                // Informações de agendamento
                cout << "Digite a data do agendamento (dd-mm-aaaa): ";
                cin.ignore();
                getline(cin, data);
                cout << "Digite o horário de início (hh:mm): ";
                getline(cin, horarioInicio);
                cout << "Digite o horário de término (hh:mm): ";
                getline(cin, horarioFim);

                // Criar e armazenar agendamento
                Agendamento novoAgendamento(idAgendamento++, clienteEscolhido, barbeiroEscolhido, servicoEscolhido, data, horarioInicio, horarioFim);
                agendamentos.push_back(novoAgendamento);
                cout << "Agendamento realizado com sucesso!\n";
                break;
            }

            case 4: {
                // Exibir Agendamentos
                if (agendamentos.empty()) {
                    cout << "Não há agendamentos realizados ainda.\n";
                } else {
                    for (const auto& agendamento : agendamentos) {
                        agendamento.exibir();
                    }
                }
                break;
            }

            case 5: {
                // Exibir Barbeiros Cadastrados
                if (barbeiros.empty()) {
                    cout << "Nenhum barbeiro cadastrado.\n";
                } else {
                    for (const auto& barbeiro : barbeiros) {
                        cout << "Barbeiro: " << barbeiro.getNome() << " | Especialidade: " << barbeiro.getEspecialidade() << endl;
                    }
                }
                break;
            }

            case 6: {
                // Exibir Clientes Cadastrados
                if (clientes.empty()) {
                    cout << "Nenhum cliente cadastrado.\n";
                } else {
                    for (const auto& cliente : clientes) {
                        cout << "Cliente: " << cliente.getNome() << " | Telefone: " << cliente.getTelefone() << endl;
                    }
                }
                break;
            }

            case 7:
                cout << "Saindo do sistema...\n";
                break;

            default:
                cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcao != 7);

    return 0;
}
