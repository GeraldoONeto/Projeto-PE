#ifndef SIMILARIDADE_HPP
#define SIMILARIDADE_HPP

#include <vector>
#include "dados_vendas.hpp"
using namespace std;

vector<vector<int>> criarMatrizDensa(const vector<string>& codClientes, const vector<string>& nomeProdutos, const vector<vector<int>>& comprasPorCliente);
vector<vector<int>> multiplicarMatrizes(const vector<vector<int>>& A);
vector<vector<int>> multiplicarEficiente(const vector<vector<int>>& A);
vector<vector<double>> calcularSimilaridade(const vector<string>& codClientes ,const vector<vector<int>>& comprasPorCliente , const vector<vector<int>>& I);
double similaridadeEficiente(const vector<string>& codClientes, const vector<string>& nomeProdutos, const vector<vector<int>>& comprasPorCliente, int id1, int id2);
double similaridadeComum(const vector<string>& codClientes, const vector<string>& nomeProdutos, const vector<vector<int>>& comprasPorCliente, int id1, int id2);
#endif
