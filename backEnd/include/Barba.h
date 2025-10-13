#ifndef BARBA_H
#define BARBA_H

// #include <Servico.h>
#include <string>

using namespace std;


class Barba : public Servico
{
private:
    float preco;
    string descricao;

public:
    // Construtor
    Barba(float preco = 15.0, const string& descricao = "Barba Completa");

    // MÉTODOS SOBREESCRITOS (polimorfismo)
    void exibir() const override;           // mostra informações da barba
    float calcularPreco() const override;   // retorna o preço

    // MÉTODOS DE ACESSO E MODIFICAÇÃO
    float getPreco() const;
    string getDescricao() const;
    void setPreco(float novoPreco);
    void setDescricao(const string& novaDescricao);

};

#endif