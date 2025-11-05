#pragma once

#include <string>
#include <iostream>

class Servicos {
private:
    int id;
    std::string nome;
    double preco;
    int duracaoEmMinutos;

public:
    Servicos();
    Servicos(int id, const std::string& nome, double preco, int duracaoEmMinutos);
    Servicos(const std::string& nome, double preco, int duracaoEmMinutos);

    int getId() const;
    void setId(int novoId);

    std::string getNome() const;
    void setNome(const std::string& novoNome);

    double getPreco() const;
    void setPreco(double novoPreco);

    int getDuracao() const;
    void setDuracao(int novaDuracao);

    void exibirDados() const;
};