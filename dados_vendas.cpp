#include "dados_vendas.hpp"
#include <stdio.h>

Dados ListaCompras(string pathArquivo) {
    Dados dados;
    FILE *arquivo = fopen(pathArquivo.c_str(), "r");
    if (arquivo == NULL) {
        printf("Erro ao tentar abrir o arquivo!\n");
        return dados;
    }

    char cabecalho[100];
    fgets(cabecalho, sizeof(cabecalho), arquivo);

    char cliente[9], produto[50];
    while (fscanf(arquivo, "%*d,%8[^,],%*d,%49[^\n]\n", cliente, produto) == 2) {
        if (dados.mapClientes.count(cliente) == 0) {
            dados.mapClientes[cliente] = dados.codClientes.size();
            dados.codClientes.push_back(cliente);
        }
        if (dados.mapProdutos.count(produto) == 0) {
            dados.mapProdutos[produto] = dados.nomeProdutos.size();
            dados.nomeProdutos.push_back(produto);
        }
    }

    rewind(arquivo);
    fgets(cabecalho, sizeof(cabecalho), arquivo);

    dados.comprasPorCliente.resize(dados.codClientes.size());

    while (fscanf(arquivo, "%*d,%8[^,],%*d,%49[^\n]\n", cliente, produto) == 2) {
        int idcl = dados.mapClientes[cliente];
        int idpdrt = dados.mapProdutos[produto];
        dados.comprasPorCliente[idcl].push_back(idpdrt);
    }

    fclose(arquivo);
    return dados;
}