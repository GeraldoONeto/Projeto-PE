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


vector<int> recomendacao(
    int idcl,
    const vector<string>& codClientes, 
    const vector<string>& nomeProdutos, 
    const vector<vector<int>>& comprasPorCliente, 
    int k){

    vector<vector<int>> A = criarMatrizDensa(codClientes, nomeProdutos, comprasPorCliente);
    vector<vector<int>> C = multiplicarEficiente(A);    
    vector<vector<double>> Vsim = calcularSimilaridade(codClientes, comprasPorCliente, C);

    int numclientes = codClientes.size();

    int* L = (int*)malloc(numclientes * sizeof(int));
    int tamL = 0;

    for (int i = 0; i < numclientes; i++){
        if(i != idcl && Vsim[idcl][i] < 1.0){
            L[tamL] = i;
            tamL += 1;
        }
    }

    int numProdutos = nomeProdutos.size();
    vector<RankProduto> R (numProdutos);

    for (int i = 0; i < numProdutos; i++){
        R[i].idProduto = i;
        R[i].valor = 1;
    }

    for (int i = 0; i < tamL; i++){
        int s = L[i];
        double sim = Vsim[idcl][s];
        for(size_t j = 0; j < comprasPorCliente[s].size(); j++){
            int id_p = comprasPorCliente[s][j];

            bool existeEmC = false;

            for(size_t x = 0; x < comprasPorCliente[idcl].size(); x++){
                if(comprasPorCliente[idcl][x] == id_p){
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

    vector<int> prodRecomendados; 

    for (int i = 0; i < k; i++){
        prodRecomendados.push_back(R[i].idProduto);
    }

    free(L);

    return prodRecomendados;
}