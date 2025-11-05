#pragma once
#include "Funcionario.h"
#include <iostream>

class Gestor : public Funcionario {
public:
    Gestor(int id, const std::string& nome,
        const std::string& email, const std::string& telefone, float salario)
        : Funcionario(id, nome, email, telefone, salario) {}
    Gestor(const std::string& nome,
        const std::string& email, const std::string& telefone, float salario)
        : Funcionario(nome, email, telefone, salario) {}

    // Demitir subordinado pelo nome
   /* void demitirFuncionario(const std::string& nome) {
        if (removerSubordinado(nome)) {
            std::cout << "Funcionario " << nome << " demitido com sucesso." << std::endl;
        }
        else {
            std::cout << "Funcionario " << nome << " nao encontrado." << std::endl;
        }
    }

    // Aumentar salário de subordinado pelo nome
    void aumentarSalarioFuncionario(const std::string& nome, float valor) {
        for (auto& f : subordinados) {
            if (f->getNome() == nome) {
                f->aumentarSalario(valor);
                std::cout << "Salario de " << nome << " aumentado em " << valor << std::endl;
                break;
            }
        }
    }*/
};