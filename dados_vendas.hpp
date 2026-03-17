#ifndef DADOS_VENDAS_HPP
#define DADOS_VENDAS_HPP

#include <vector>
#include <map>
#include <string>
using namespace std;

typedef struct {
    vector<string> codClientes;
    map<string, int> mapClientes;
    vector<string> nomeProdutos;
    map<string, int> mapProdutos;
    vector<vector<int>> comprasPorCliente;
} Dados;

Dados ListaCompras(string pathArquivo);

#endif