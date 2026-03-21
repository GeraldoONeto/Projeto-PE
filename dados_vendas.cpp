#include "dados_vendas.hpp"
#include <stdio.h>

Dados listaCompras(const char* pathArquivo) { //usar char e passar por ref
    Dados dados;
    FILE *arquivo = fopen(pathArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao tentar abrir o arquivo!\n");
        return dados;
    }

    char cabecalho[100];
    fgets(cabecalho, sizeof(cabecalho), arquivo);

    char cliente[9], produto[50];
    while (fscanf(arquivo, "%*d,%8[^,],%*d,%49[^\n]\n", cliente, produto) == 2) {
        if (dados.mapClientes.find(cliente) == dados.mapClientes.end()) { 
            dados.mapClientes[cliente] = dados.codClientes.size();
            dados.codClientes.push_back(cliente);

            dados.comprasPorCliente.push_back(vector<int>());
        }
        if (dados.mapProdutos.find(produto) == dados.mapClientes.end()) {
            dados.mapProdutos[produto] = dados.nomeProdutos.size();
            dados.nomeProdutos.push_back(produto);
        }

        int idcl = dados.mapClientes[cliente];
        int idpdrt = dados.mapProdutos[produto];
        dados.comprasPorCliente[idcl].push_back(idpdrt);

    }

    fclose(arquivo);
    return dados;
}
