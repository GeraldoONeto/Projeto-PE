#ifndef SIMILARIDADE_HPP
#define SIMILARIDADE_HPP

#include <vector>
#include "dados_vendas.hpp"
using namespace std;

vector<vector<int>> criarMatrizDensa(const Dados& dados);
vector<vector<int>> multiplicarMatrizes(const vector<vector<int>>& A);
vector<vector<int>> multiplicarEficiente(const vector<vector<int>>& A);
vector<vector<double>> calcularSimilaridade(const Dados& dados, const vector<vector<int>>& I);
//vector<vector<double>> calcularSimEfi(const Dados& dados, const vector<vector<int>>& C); 
double obterSimilaridade(const Dados& dados, const vector<vector<double>>& S, int i, int j);
//double obterSimEfi(const Dados& dados, const vector<vector<double>>& SE, int i, int j);

#endif
