#ifndef RECOMENDACAO_HPP
#define RECOMENDACAO_HPP

#include <vector>
#include "dados_vendas.hpp"

using namespace std;

typedef struct{
    int idProduto;
    double valor;
} RankProduto;

vector<RankProduto> recomendacao(int idcl, const Dados& dados, const vector<vector<double>>& S, int k);

#endif