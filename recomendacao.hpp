#ifndef RECOMENDACAO_HPP
#define RECOMENDACAO_HPP

#include <vector>
#include "dados_vendas.hpp"

using namespace std;

typedef struct{
    int idProduto;
    double valor;
} RankProduto;

vector<int> recomendacao(int idcl,const vector<string>& codClientes, const vector<string>& nomeProdutos, const vector<vector<int>>& comprasPorCliente, int k);

#endif