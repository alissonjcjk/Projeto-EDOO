#include "../include/Cliente.h"

void Cliente::setHistorico(string servico){
    historicoServicos.push_back(servico);
};
void Cliente::getHistorico(){
    for (const auto servico : historicoServicos) {
        cout << "-" << servico << endl;
    }
};