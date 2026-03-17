#ifndef SIMILARIDADE_HPP
#define SIMILARIDADE_HPP

#include <vector>
#include "dados_vendas.hpp"

std::vector<std::vector<int>> criarMatrizDensa(const Dados& dados);
std::vector<std::vector<int>> multiplicarMatrizes(const std::vector<std::vector<int>>& A);
std::vector<std::vector<double>> calcularSimilaridade(const Dados& dados, const std::vector<std::vector<int>>& I);
double obterSimilaridade(const Dados& dados, const std::vector<std::vector<double>>& S, int i, int j);

#endif