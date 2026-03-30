#include "similaridade.hpp"
#include <stdio.h>

using namespace std;

vector<vector<int>> criarMatrizDensa(
    const vector<string>& codClientes, 
    const vector<string>& nomeProdutos, 
    const vector<vector<int>>& comprasPorCliente) {

    int nClientes = codClientes.size();
    int nProdutos = nomeProdutos.size();
    vector<vector<int>> A(nClientes, vector<int>(nProdutos, 0));

    for (int i = 0; i < nClientes; i++) {
        const vector<int>& compras = comprasPorCliente[i];
        for (size_t j = 0; j < compras.size(); j++) {
            int prod = compras[j];
            A[i][prod] = 1;
        }
    }
    return A;
}


vector<vector<int>> multiplicarMatrizes(const vector<vector<int>>& A) {
    int n = A.size();
    int m = A[0].size();
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

vector<vector<int>> multiplicarEficiente(const vector<vector<int>>& A) {
    int n = A.size();
    int m = A[0].size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int soma = 0;
            for (int k = 0; k < m; k++) {
                soma += A[i][k] * A[j][k];
            }
            C[i][j] = soma; 
            C[j][i] = soma; 
        }
    }
    return C;
}

vector<vector<double>> calcularSimilaridade(
    const vector<string>& codClientes,
    const vector<vector<int>>& comprasPorCliente,
    const vector<vector<int>>& I) {
    int n = codClientes.size();
    vector<vector<double>> S(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        double tam_i = (double)comprasPorCliente[i].size();
        for (int j = 0; j < n; j++) {

            S[i][j] = 1.0 - (double)I[i][j] / tam_i;
            
        }
    }
    return S;
}

double similaridadeEficiente(
    const vector<string>& codClientes, 
    const vector<string>& nomeProdutos, 
    const vector<vector<int>>& comprasPorCliente,
    int id1, int id2) {

    vector<vector<int>> C;
    {
        vector<vector<int>> A = criarMatrizDensa(codClientes, nomeProdutos, comprasPorCliente);
        C = multiplicarEficiente(A);
    }
    
    
    vector<vector<double>> S_eficiente = calcularSimilaridade(codClientes, comprasPorCliente, C);
                
 
    return S_eficiente[id1][id2];
}

double similaridadeComum(
    const vector<string>& codClientes, 
    const vector<string>& nomeProdutos, 
    const vector<vector<int>>& comprasPorCliente,
    int id1, int id2) {

    vector<vector<int>> I;    
    {
        vector<vector<int>> A = criarMatrizDensa(codClientes, nomeProdutos, comprasPorCliente);
        I = multiplicarMatrizes(A);
    }
    vector<vector<double>> S_comum = calcularSimilaridade(codClientes, comprasPorCliente, I);
                
    return S_comum[id1][id2];
}