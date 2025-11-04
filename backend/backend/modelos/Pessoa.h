#pragma once
#include <string>

class Pessoa {
private:
    int id;
    std::string nome;
    std::string email;
    std::string telefone;

public:
    Pessoa() : id(0), nome(""), email(""), telefone("") {}

    Pessoa(int id, const std::string& nome, const std::string& email, const std::string& telefone);

    Pessoa(const std::string& nome, const std::string& email, const std::string& telefone);

    void setNome(const std::string& nome);
    void setEmail(const std::string& email);
    void setTelefone(const std::string& telefone);

    int getId() const;
    std::string getNome() const;
    std::string getEmail() const;
    std::string getTelefone() const;
};
