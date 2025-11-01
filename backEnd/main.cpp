#include <iostream>
#include <vector>
#include <string>
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

    int idAgendamentoCliente = 1;
    int idAgendamentoBarbeiro = 1;
    int idAgendamento = 1;
    int idCadastroServico = 1;
    int idServico;
    string nome, telefone, email,servicoPrefe,especialidade;

    int opcao;


    do {
        cout << "\n===== MENU BARBEARIA =====\n";
        cout << "1. Cadastrar Cliente\n";
        cout << "2. Cadastrar Barbeiro\n";
        cout << "3. Agendar Horário\n";
        cout << "4. Exibir Agendamentos\n";
        cout << "5. Exibir Barbeiros Cadastrados\n";
        cout << "6. Exibir Clientes Cadastrados\n";
        cout << "7. cadastrar servico\n";
        cout << "8. Sair\n";
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
                clientes.push_back(Cliente(idAgendamentoCliente,nome, email,telefone,servicoPrefe));
                idAgendamentoCliente +=1;
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
                barbeiros.push_back(Barbeiro(6,20,idAgendamentoBarbeiro,nome,email,telefone));
                idAgendamentoBarbeiro +=1;
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
                cin >> idAgendamentoCliente;
                Cliente* clienteEscolhido = &clientes[idAgendamentoCliente - 1];

                // Escolher barbeiro
                cout << "Escolha o barbeiro (1 a " << barbeiros.size() << "): ";
                cin >> idAgendamentoBarbeiro;
                Barbeiro* barbeiroEscolhido = &barbeiros[idAgendamentoBarbeiro - 1];

                // Escolher serviço
                cout << "Escolha o serviço (1 a " << servicos.size() << "): ";
                cin >> idServico;
                Servico* servicoEscolhido = &servicos[idServico - 1];

                // Informações de agendamento
                cout << "Digite a data do agendamento (dd-mm-aaaa): ";
                cin.ignore();
                getline(cin, data);
                cout << "Digite o horário de início : ";
                cin>>horarioInicio;
                cout << "Digite o horário de término: ";
                cin >> horarioFim;

                // Criar e armazenar agendamento
                Agendamento novoAgendamento;
                novoAgendamento.setAgendamento(idAgendamento,clienteEscolhido,barbeiroEscolhido,servicoEscolhido,data,to_string(horarioInicio),to_string(horarioFim));
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
                        cout << "Barbeiro: " << barbeiro.getNome()<< endl;
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
                        cout << "Cliente: " << cliente.getNome() << " Serviço preferido: " << cliente.getServicoPreferido()<<  endl;
                    }
                }
                break;
            }

            case 7:
                {Servico servicoCadastro(idCadastroServico);
                idCadastroServico +=1;
                float preco;
                int duracao; 
                cout << "informe o servico que deseja cadastrar\n";
                cin.ignore();
                getline(cin, nome);
                cout << "informe o valor (float)\n";
                cin >> preco;
                cout << "informe a duracao (inteiro)\n";
                cin >> duracao;
                cout << "";
                servicoCadastro.setServico(nome,preco,duracao);
                servicos.push_back(servicoCadastro);
                break;}
            case 8:
                cout << "saindo da aplicação \n";
                break;

            default:
                cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcao != 8);

    return 0;
}
