#include <iostream>
#include "Cliente.h"

using namespace std;

int main() {
    // Criando um cliente
    Cliente c1(1, "Flávio Araújo", "flavio@email.com", "99999-9999", "Corte de cabelo");

    // Exibindo informações básicas (usando os getters da classe Pessoa)
    cout << "=== Dados do Cliente ===" << endl;
    cout << "ID: " << c1.getId() << endl;
    cout << "Nome: " << c1.getNome() << endl;
    cout << "Email: " << c1.getEmail() << endl;
    cout << "Telefone: " << c1.getTelefone() << endl;
    cout << "Serviço preferido: " << c1.getServicoPreferido() << endl;

    // Alterando o serviço preferido
    c1.setServicoPreferido("Barba completa");
    cout << "======Serviço preferido atualizado======" << endl<< c1.getServicoPreferido() << endl;

    return 0;
}
// g++ -Iinclude src/Pessoa.cpp src/Cliente.cpp main.cpp -o main