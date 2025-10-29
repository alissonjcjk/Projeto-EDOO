#include <iostream>

using namespace std;

class Servico{
    private:
        int id;
        string nome;
        float preco;
        int duracao;
    public:
        Servico(int id);
        void setServico(string nome, float preco, int duracao); 
};