#include <stdio.h>
#include <stdlib.h>
#include <algorithm> 
#include <vector>

#include "recomendacao.hpp"
#include "dados_vendas.hpp"
#include "similaridade.hpp"

using namespace std;

bool compararPorRank(const RankProduto& a, const RankProduto& b){
        return a.valor < b.valor;
    }


vector<RankProduto> recomendacao(int idcl, const Dados& dados, const vector<vector<double>>& Vsim, int k){

int numclientes = dados.codClientes.size();

int* L = (int*)malloc(numclientes * sizeof(int));
int tamL = 0;

for (int i = 0; i < numclientes; i++){
    if(i != idcl && Vsim[idcl][i] < 1.0){
        L[tamL] = i;
        tamL += 1;
    }
}

int numProdutos = dados.nomeProdutos.size();
vector<RankProduto> R (numProdutos);

for (int i = 0; i < numProdutos; i++){
    R[i].idProduto = i;
    R[i].valor = 1;
}

for (int i = 0; i < tamL; i++){
    int s = L[i];
    double sim = Vsim[idcl][s];
    for(size_t j = 0; j < dados.comprasPorCliente[s].size(); j++){
        int id_p = dados.comprasPorCliente[s][j];

        bool existeEmC = false;

        for(int x = 0; x < dados.comprasPorCliente[idcl].size(); x++){
            if(dados.comprasPorCliente[idcl][x] == id_p){
                existeEmC = true;
                break;
            }
        }

        if(existeEmC == false){
            R[id_p].valor = R[id_p].valor * sim;
        }
    }
}    
sort(R.begin(), R.end(), compararPorRank);

vector<RankProduto> prodRecomendados;

for (int i = 0; i < k; i++){
    prodRecomendados.push_back(R[i]);
}

free(L);

return prodRecomendados;
}