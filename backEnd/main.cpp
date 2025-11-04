#include <iostream>
#include <vector>
#include <string>
#include "Cliente.h"
#include "Barbeiro.h"
#include "Servico.h"
#include "Agendamento.h"
#include "Gestor.h"
#include "ArquivoManager.h"
#include <sstream>

using namespace std;

int main() {
    vector<Cliente> clientes;
    vector<Barbeiro> barbeiros;
    vector<Servico> servicos;
    vector<Agendamento> agendamentos;
    vector<Gestor> gestores;

    // Carregar dados dos arquivos
    ArquivoManager::carregarClientes(clientes);
    ArquivoManager::carregarBarbeiros(barbeiros);
    ArquivoManager::carregarServicos(servicos);
    ArquivoManager::carregarAgendamentos(agendamentos);

    // Inicializar IDs baseados nos dados carregados
    int idAgendamentoCliente = ArquivoManager::obterUltimoIdCliente();
    int idAgendamentoBarbeiro = ArquivoManager::obterUltimoIdBarbeiro();
    int idAgendamento = ArquivoManager::obterUltimoIdAgendamento();
    int idCadastroServico = ArquivoManager::obterUltimoIdServico();
    
    int idServico;
    string nome, telefone, email, servicoPrefe, especialidade;

    int opcao;

    do {
        cout << "\n===== MENU BARBEARIA =====\n";
        cout << "1. Cadastrar Cliente\n";
        cout << "2. Cadastrar Barbeiro\n";
        cout << "3. Agendar Horário\n";
        cout << "4. Exibir Agendamentos\n";
        cout << "5. Exibir Barbeiros Cadastrados\n";
        cout << "6. Exibir Clientes Cadastrados\n";
        cout << "7. Cadastrar Servico\n";
        cout << "8. Salvar Dados\n";
        cout << "9. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                // Cadastrar Cliente
                cout << "Digite o nome do cliente: ";
                cin.ignore();  
                getline(cin, nome);
                cout << "Digite o email do cliente: ";
                getline(cin, email);
                cout << "Digite o telefone do cliente: ";
                getline(cin, telefone);
                cout << "Digite o servico preferido do cliente: ";
                getline(cin, servicoPrefe);
                clientes.push_back(Cliente(idAgendamentoCliente, nome, email, telefone, servicoPrefe));
                idAgendamentoCliente += 1;
                cout << "Cliente cadastrado com sucesso!\n";
                break;
            }

            case 2: {
                // Cadastrar Barbeiro
                cout << "Digite o nome do barbeiro: ";
                cin.ignore();  
                getline(cin, nome);
                cout << "Digite o email do Barbeiro: ";
                getline(cin, email);
                cout << "Digite o telefone do Barbeiro: ";
                getline(cin, telefone);
                cout << "Digite a especialidade do Barbeiro: ";
                getline(cin, especialidade);
                
                Barbeiro novoBarbeiro(6, 20, idAgendamentoBarbeiro, nome, email, telefone,especialidade);
                barbeiros.push_back(novoBarbeiro);
                idAgendamentoBarbeiro += 1;
                cout << "Barbeiro cadastrado com sucesso!\n";
                break;
            }

            case 3: {
                // Agendar horário
                if (clientes.empty() || barbeiros.empty() || servicos.empty()) {
                    cout << "Certifique-se de que há clientes, barbeiros e serviços cadastrados antes de agendar!\n";
                    break;
                }

                string data;
                int horarioInicio, horarioFim;
                
                // Escolher cliente
                cout << "Escolha o cliente (1 a " << clientes.size() << "): ";
                for (size_t i = 0; i < clientes.size(); i++) {
                    cout << "\n" << (i + 1) << ". " << clientes[i].getNome();
                }
                cout << "\nOpção: ";
                cin >> idAgendamentoCliente;
                Cliente* clienteEscolhido = &clientes[idAgendamentoCliente - 1];

                // Escolher barbeiro
                cout << "Escolha o barbeiro (1 a " << barbeiros.size() << "): ";
                for (size_t i = 0; i < barbeiros.size(); i++) {
                    cout << "\n" << (i + 1) << ". " << barbeiros[i].getNome();
                }
                cout << "\nOpção: ";
                cin >> idAgendamentoBarbeiro;
                Barbeiro* barbeiroEscolhido = &barbeiros[idAgendamentoBarbeiro - 1];

                // Escolher serviço
                cout << "Escolha o serviço (1 a " << servicos.size() << "): ";
                for (size_t i = 0; i < servicos.size(); i++) {
                    cout << "\n" << (i + 1) << ". " << servicos[i].getNome() << " - R$ " << servicos[i].getPreco();
                }
                cout << "\nOpção: ";
                cin >> idServico;
                Servico* servicoEscolhido = &servicos[idServico - 1];

                // Informações de agendamento
                cout << "Digite a data do agendamento (dd-mm-aaaa): ";
                cin.ignore();
                getline(cin, data);
                cout << "Digite o horário de início: ";
                cin >> horarioInicio;
                cout << "Digite o horário de término: ";
                cin >> horarioFim;

                // Criar e armazenar agendamento
                Agendamento novoAgendamento;
                novoAgendamento.setAgendamento(idAgendamento, clienteEscolhido, barbeiroEscolhido, servicoEscolhido, data, to_string(horarioInicio), to_string(horarioFim));
                agendamentos.push_back(novoAgendamento);
                idAgendamento += 1;
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
                        cout << "ID: " << barbeiro.getId() << " | Barbeiro: " << barbeiro.getNome() 
                             << " | Especialidade: " << barbeiro.getEspecialidade() << endl;
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
                        cout << "ID: " << cliente.getId() << " | Cliente: " << cliente.getNome() 
                             << " | Serviço preferido: " << cliente.getServicoPreferido() << endl;
                    }
                }
                break;
            }

            case 7: {
                // Cadastrar Serviço
                Servico servicoCadastro(idCadastroServico);
                idCadastroServico += 1;
                float preco;
                int duracao; 
                cout << "Informe o serviço que deseja cadastrar: ";
                cin.ignore();
                getline(cin, nome);
                cout << "Informe o valor (float): ";
                cin >> preco;
                cout << "Informe a duração (inteiro): ";
                cin >> duracao;
                servicoCadastro.setServico(nome, preco, duracao);
                servicos.push_back(servicoCadastro);
                cout << "Serviço cadastrado com sucesso!\n";
                break;
            }

            case 8: {
                // Salvar dados nos arquivos
                ArquivoManager::salvarClientes(clientes);
                ArquivoManager::salvarBarbeiros(barbeiros);
                ArquivoManager::salvarServicos(servicos);
                ArquivoManager::salvarAgendamentos(agendamentos);
                cout << "Dados salvos com sucesso!\n";
                break;
            }

            case 9:
                // Salvar dados antes de sair
                ArquivoManager::salvarClientes(clientes);
                ArquivoManager::salvarBarbeiros(barbeiros);
                ArquivoManager::salvarServicos(servicos);
                ArquivoManager::salvarAgendamentos(agendamentos);
                cout << "Dados salvos. Saindo da aplicação...\n";
                break;

            default:
                cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcao != 9);

    return 0;
}