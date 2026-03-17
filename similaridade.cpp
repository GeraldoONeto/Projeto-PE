#include "similaridade.hpp"
#include <stdio.h>

using namespace std;

vector<vector<int>> criarMatrizDensa(const Dados& dados) {
    int nClientes = dados.codClientes.size();
    int nProdutos = dados.nomeProdutos.size();
    vector<vector<int>> A(nClientes, vector<int>(nProdutos, 0));

    for (int i = 0; i < nClientes; i++) {
        const vector<int>& compras = dados.comprasPorCliente[i];
        for (size_t j = 0; j < compras.size(); j++) {
            int prod = compras[j];
            A[i][prod] = 1;
        }
    }
    return A;
}

vector<vector<int>> multiplicarMatrizes(const vector<vector<int>>& A) {
    int n = A.size();          // clientes
    int m = A[0].size();       // produtos
    vector<vector<int>> I(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int soma = 0;
            for (int k = 0; k < m; k++) {
                soma += A[i][k] * A[j][k];
            }
            I[i][j] = soma;
        }
    }
    return I;
}

vector<vector<double>> calcularSimilaridade(const Dados& dados, const vector<vector<int>>& I) {
    int n = dados.codClientes.size();
    vector<vector<double>> S(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        int tam_i = dados.comprasPorCliente[i].size();
        if (tam_i == 0) {
            for (int j = 0; j < n; j++) S[i][j] = 1.0;
            continue;
        }
        for (int j = 0; j < n; j++) {
            S[i][j] = 1.0 - (double)I[i][j] / tam_i;
        }
    }
    return S;
}

double obterSimilaridade(const Dados& dados, const vector<vector<double>>& S, int i, int j) {
    return S[i][j];
}